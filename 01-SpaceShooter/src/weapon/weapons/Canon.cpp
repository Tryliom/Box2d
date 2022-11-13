#include "weapon/weapons/Canon.h"

#include "Game.h"
#include "manager/ProjectileManager.h"
#include "projectile/bullets/CanonBullet.h"

Canon::Canon(Stats::WeaponStats& userStats) :
	Weapon(Stats::WeaponStats{
		.Damage = 20.f,
		.Speed = 500.f,
		.Spread = 15.f,
		.Range = 10000.f,
		.BulletsPerShot = 1,
		.Cooldown = 0.8f,
		.Size = 1.5f
	}, userStats) {}

void Canon::shootBullet(b2Body* body, const sf::Vector2f position, const float angle, const b2Vec2 velocity, const Group bulletGroup)
{
	const Stats::WeaponStats stats = getTotalStats();

	ProjectileManager::GetInstance().AddProjectile(new CanonBullet(
		body, position, angle,
		stats.GetSize(), velocity, getLifeTime(),
		stats.GetDamage(), bulletGroup
	));
}