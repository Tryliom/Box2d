#include "weapon/weapons/Canon.h"

#include "Game.h"
#include "projectile/bullets/RegularBullet.h"

Canon::Canon(Stats::WeaponStats& userStats) :
	Weapon(Stats::WeaponStats{
		.Damage = 20.f,
		.Speed = 50.f,
		.Spread = 15.f,
		.Range = 100.f,
		.BulletsPerShot = 1,
		.Cooldown = 0.8f,
		.Size = 1.5f
	}, userStats) {}

void Canon::shootBullet(b2Body* body, const sf::Vector2f position, const float angle, const b2Vec2 velocity, const Group bulletGroup)
{
	const Stats::WeaponStats stats = getTotalStats();

	ProjectileManager::GetInstance().AddProjectile(new RegularBullet(
		body, position, angle,
		stats.GetSize(), velocity, getLifeTime(),
		stats.GetDamage(), bulletGroup
	));
}