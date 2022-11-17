#include "weapon/weapons/ShotGun.h"

#include "manager/ProjectileManager.h"
#include "projectile/bullets/ShotGunBullet.h"

ShotGun::ShotGun(Entity* user) :
	Weapon(Stats::WeaponStats{
		.Damage = 3.f,
		.Speed = 1000.f,
		.Spread = 50.f,
		.Range = 300.f,
		.BulletsPerShot = 40,
		.Cooldown = 1.f,
		.Size = 1.f
	}, user) {}

void ShotGun::shootBullet(b2Body* body, const sf::Vector2f position, const float angle, const b2Vec2 velocity, const Group bulletGroup)
{
	const Stats::WeaponStats stats = getTotalStats();

	ProjectileManager::GetInstance().AddProjectile(new ShotGunBullet(
		body, position, angle,
		stats.GetSize(), velocity, getLifeTime(),
		stats.GetDamage(), bulletGroup
	));
}