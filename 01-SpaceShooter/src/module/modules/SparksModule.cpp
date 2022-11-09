#include "module/modules/SparksModule.h"

#include "Game.h"
#include "Random.h"
#include "entity/Entity.h"

SparksModule::SparksModule()
{
	_sparks = {};
	_sparksCurrentCooldown = sf::Time::Zero;
	_sparksPerSecond = 20.0f;
	_sparksAngle = 90.0f;
	_sparksCooldown = sf::seconds(1.0f / _sparksPerSecond);
}

void SparksModule::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	for (auto& spark : _sparks)
	{
		target.draw(spark, states);
	}
}

void SparksModule::updateData(Entity* entity)
{
	const Stats::EntityStats stats = entity->GetTotalStats();

	_sparksAngle = 90.0f * (0.5f + stats.GetSpeed());
	_sparksPerSecond = 20.f * (0.5f + stats.GetSpeed());
	_sparksCooldown = sf::seconds(1.0f / _sparksPerSecond);
}

void SparksModule::addSparks(float angleDegree, const Entity* entity)
{
	const sf::RectangleShape shape = entity->GetShape();
	const sf::Vector2f position = shape.getPosition();
	const Stats::EntityStats stats = entity->GetTotalStats();
	const Stats::WeaponStats weaponStats = entity->GetWeaponStats();

	// Calculate the position of the sparks
	const float x = position.x - (shape.getSize().x / 5.f) * std::cos(Game::DegreeToRad(angleDegree));
	const float y = position.y - (shape.getSize().y / 5.f) * std::sin(Game::DegreeToRad(angleDegree));

	const float sparksSpeed = stats.GetSpeed() * 50.f;
	angleDegree -= 90.f;

	_sparks.emplace_back(Spark(
		entity->GetGame().GetNewBody(), sf::Vector2f(x, y),
		angleDegree, 1.5f + weaponStats.GetSize(), Game::GetLinearVelocity(sparksSpeed, angleDegree), stats.GetSpeed() * 20.f, entity->GetProjectileGroup()
	));
}

void SparksModule::Initialize(Entity* entity)
{
	updateData(entity);
}

void SparksModule::Update(const sf::Time elapsed, Entity* entity)
{
	updateData(entity);

	_sparksCurrentCooldown += elapsed;

	for (auto& spark : _sparks)
	{
		spark.Update(elapsed);
	}

	// Remove the sparks that are dead
	_sparks.erase(std::remove_if(_sparks.begin(), _sparks.end(), [](const Spark& spark) { return spark.IsDead(); }), _sparks.end());
}

void SparksModule::OnEntityMove(Entity* entity)
{
	if (_sparksCurrentCooldown >= _sparksCooldown)
	{
		_sparksCurrentCooldown = sf::Time::Zero;

		const float anglePosition = entity->GetShape().getRotation() - 90.f;

		addSparks(Random::GetFloat(anglePosition - _sparksAngle / 2.f, anglePosition), entity);
		addSparks(Random::GetFloat(anglePosition, anglePosition + _sparksAngle / 2.f), entity);
	}
}
