#include "weapon/weapons/Sniper.h"

#include "projectile/bullets/PenetrationBullet.h"
#include "Game.h"

Sniper::Sniper(Stats::WeaponStats& userStats) :
	Weapon(Stats::WeaponStats{
		.Damage = 50.f,
		.Speed = 150.f,
		.Spread = 0.f,
		.Range = 1000.f,
		.BulletsPerShot = 1,
		.Cooldown = 1.f,
		.Size = 1.5f
	}, userStats)
{}

void Sniper::shootBullet(const sf::Vector2f position, const float angle, const b2Vec2 velocity, const Group bulletGroup)
{
	const Stats::WeaponStats stats = getTotalStats();

	Game::GetInstance().GetProjectileManager().AddProjectile(new PenetrationBullet(
		position, angle,
		stats.GetSize(), velocity, getLifeTime(),
		stats.GetDamage(), bulletGroup, true
	));
}
