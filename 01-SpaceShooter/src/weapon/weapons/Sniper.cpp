#include "weapon/weapons/Sniper.h"

#include "projectile/bullets/PenetrationBullet.h"
#include "Game.h"
#include "manager/ProjectileManager.h"

Sniper::Sniper(Stats::WeaponStats& userStats) :
	Weapon(Stats::WeaponStats{
		.Damage = 50.f,
		.Speed = 1500.f,
		.Spread = 10.f,
		.Range = 10000.f,
		.BulletsPerShot = 1,
		.Cooldown = 1.f,
		.Size = 1.5f
	}, userStats)
{}

void Sniper::shootBullet(b2Body* body, const sf::Vector2f position, const float angle, const b2Vec2 velocity, const Group bulletGroup)
{
	const Stats::WeaponStats stats = getTotalStats();

	ProjectileManager::GetInstance().AddProjectile(new PenetrationBullet(
		body, position, angle,
		stats.GetSize(), velocity, getLifeTime(),
		stats.GetDamage(), bulletGroup, true
	));
}