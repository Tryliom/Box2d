#include "weapon/weapons/Canon.h"

#include <iostream>

#include "Game.h"
#include "animation/chargeAnimations/CircleAttackCharge.h"
#include "projectile/bullets/RegularBullet.h"

Canon::Canon(Stats::WeaponStats& userStats) :
	Weapon(Stats::WeaponStats{
		.Damage = 20.f,
		.Speed = 50.f,
		.Range = 1000.f,
		.BulletsPerShot = 1,
		.Cooldown = 1.5f
	}, userStats)
{
	
}

sf::Vector2f Canon::getFrontPosition(const Entity& entity) const
{
	const sf::Vector2f size = entity.GetShape().getSize();
	const sf::Vector2f position = entity.GetShape().getPosition();

	const float angle = entity.GetShape().getRotation() + 90.f;
	const float x = position.x - (size.x * 0.5f) * std::cos(Game::DegreeToRad(angle));
	const float y = position.y - (size.y * 0.5f) * std::sin(Game::DegreeToRad(angle));

	return { x, y };
}

void Canon::StartCharging(Entity entity)
{
	Weapon::StartCharging(entity);

	const sf::Vector2f size = entity.GetShape().getSize();

	_chargeAnimation = new CircleAttackCharge(entity.GetPosition(), (size.x + size.y) / 2.f, getTotalStats().GetCooldown());
}

void Canon::Shoot(const Entity entity, const Group bulletGroup)
{
	Weapon::Shoot(entity, bulletGroup);

	//TODO: Apply spread and multiple bullets per shot

	const Stats::WeaponStats stats = getTotalStats();
	const float angle = Game::RadToDegree(entity.GetBody()->GetAngle());
	const sf::Time lifeTime = getLifeTime();
	const b2Vec2 velocity = Game::GetLinearVelocity(stats.GetSpeed(), angle);

	_bullets.emplace_back(new RegularBullet(
		entity.GetGame().GetNewBody(), getFrontPosition(entity),
		angle, velocity, lifeTime,
		stats.GetDamage(), false, bulletGroup
	));
}