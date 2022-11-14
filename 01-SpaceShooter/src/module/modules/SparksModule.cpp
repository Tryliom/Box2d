#include "module/modules/SparksModule.h"

#include <iostream>

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
	const Stats::WeaponStats weaponStats = entity->GetWeaponStats();

	_sparksAngle = 90.0f + weaponStats.GetSpread();
	_sparksPerSecond = 25.f + weaponStats.GetBulletsPerShot();
	_sparksCooldown = sf::seconds(1.0f / _sparksPerSecond);

	if (_sparksAngle > 160.f)
	{
		_sparksAngle = 160.f;
	}
}

void SparksModule::addSparks(float angleDegree, Entity* entity)
{
	const sf::RectangleShape shape = entity->GetShape();
	const sf::Vector2f scale = shape.getScale();
	const sf::Vector2f position = shape.getPosition();
	const Stats::EntityStats stats = entity->GetTotalStats();
	const Stats::WeaponStats weaponStats = entity->GetWeaponStats();

	// Calculate the position of the sparks
	const float x = position.x - (shape.getSize().x * scale.x / 5.f) * std::cos(Game::DegreeToRad(angleDegree));
	const float y = position.y - (shape.getSize().y * scale.y / 5.f) * std::sin(Game::DegreeToRad(angleDegree));

	angleDegree -= 90.f;

	_sparks.emplace_back(
		entity->GetGame().GetNewBody(), sf::Vector2f(x, y),
		angleDegree, 2.f + weaponStats.GetSize(), Game::GetLinearVelocity(stats.GetSpeed(), angleDegree), sf::seconds(0.5f),
		stats.GetSpeed(), entity->GetProjectileGroup()
	);
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
	_sparks.erase(std::remove_if(_sparks.begin(), _sparks.end(), [](const PenetrationBullet& spark)
	{
		if (spark.IsDead())
		{
			spark.GetBody()->GetWorld()->DestroyBody(spark.GetBody());

			return true;
		}

		return false;
	}), _sparks.end());
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
