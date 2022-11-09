#include "weapon/weapons/Canon.h"

#include <iostream>

#include "Game.h"
#include "animation/chargeAnimations/CircleAttackCharge.h"
#include "projectile/bullets/RegularBullet.h"

Canon::Canon(Stats::WeaponStats& userStats) :
	Weapon(Stats::WeaponStats{
		.Damage = 20.f,
		.Speed = 50.f,
		.Spread = 15.f,
		.Range = 500.f,
		.BulletsPerShot = 1,
		.Cooldown = 1.f,
		.Size = 1.5f
	}, userStats)
{
	
}

sf::Vector2f Canon::getFrontPosition(Entity* entity) const
{
	const sf::Vector2f size = entity->GetShape().getSize();
	const sf::Vector2f position = entity->GetShape().getPosition();

	const float angle = entity->GetShape().getRotation() + 90.f;
	const float x = position.x - (size.x * 0.5f) * std::cos(Game::DegreeToRad(angle));
	const float y = position.y - (size.y * 0.5f) * std::sin(Game::DegreeToRad(angle));

	return { x, y };
}

void Canon::StartCharging(Entity* entity)
{
	Weapon::StartCharging(entity);

	const sf::Vector2f size = entity->GetShape().getSize();

	_chargeAnimation = new CircleAttackCharge(entity->GetPosition(), (size.x + size.y) / 2.f, getTotalStats().GetCooldown());
}

void Canon::Shoot(Entity* entity, const Group bulletGroup)
{
	Weapon::Shoot(entity, bulletGroup);

	const Stats::WeaponStats stats = getTotalStats();
	const float angle = Game::RadToDegree(entity->GetBody()->GetAngle());
	const sf::Time lifeTime = getLifeTime();
	const sf::Vector2f frontPosition = getFrontPosition(entity);
	const int bulletPerShot = stats.GetBulletsPerShot();

	for (int i = 0; i < bulletPerShot; i++)
	{
		float angleAfterSpread = angle - stats.GetSpread() + stats.GetSpread() * 2.f * i / bulletPerShot;

		if (stats.GetBulletsPerShot() % 2 == 0)
		{
			angleAfterSpread += stats.GetSpread() / bulletPerShot;
		}
		else
		{
			angleAfterSpread += stats.GetSpread() / (bulletPerShot - 1);
		}

		if (bulletPerShot == 1)
		{
			angleAfterSpread = angle;
		}

		const b2Vec2 velocity = entity->GetBody()->GetLinearVelocity() + Game::GetLinearVelocity(stats.GetSpeed(), angleAfterSpread);

		_bullets.push_back(new RegularBullet(
			entity->GetGame().GetNewBody(), frontPosition,
			angleAfterSpread, stats.GetSize(), velocity, lifeTime,
			stats.GetDamage(), false, bulletGroup
		));
	}
}