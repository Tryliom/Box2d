#include "module/modules/SparksModule.h"

#include <iostream>

#include "Game.h"
#include "Random.h"
#include "entity/Entity.h"
#include "manager/ProjectileManager.h"

SparksModule::SparksModule()
{
	_sparksCurrentCooldown = sf::Time::Zero;
	_sparksPerSecond = 20.0f;
	_sparksAngle = 90.0f;
	_sparksCooldown = sf::seconds(1.0f / _sparksPerSecond);
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

void SparksModule::addSparks(float angleDegree, Entity* entity) const
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

	ProjectileManager::GetInstance().AddProjectile(new PenetrationBullet(
		entity->GetGame().GetNewBody(), sf::Vector2f(x, y),
		angleDegree, 2.f + weaponStats.GetSize(), Game::GetLinearVelocity(stats.GetSpeed(), angleDegree), sf::seconds(0.5f),
		stats.GetSpeed(), entity->GetProjectileGroup()
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

std::vector<TextLine> SparksModule::GetDescription() const
{
	return {
		TextLine({
			CustomText{.Text = "Shoot sparks from the bottom of your ship", .Size = 16},
			CustomText{.Text = "Damage scale with your ship speed", .Size = 16}
		}),
	};
}
