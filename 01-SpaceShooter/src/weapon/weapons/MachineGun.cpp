#include "weapon/weapons/MachineGun.h"

#include "manager/ProjectileManager.h"
#include "projectile/bullets/MachineGunBullet.h"

MachineGun::MachineGun(Stats::WeaponStats& userStats) :
	Weapon(Stats::WeaponStats{
		.Damage = 5.f,
		.Speed = 120.f,
		.Spread = 15.f,
		.Range = 500.f,
		.BulletsPerShot = 3,
		.Cooldown = 0.3f,
		.Size = 0.75f
	}, userStats)
{}

void MachineGun::shootBullet(b2Body* body, const sf::Vector2f position, const float angle, const b2Vec2 velocity,
	const Group bulletGroup)
{
	const Stats::WeaponStats stats = getTotalStats();

	ProjectileManager::GetInstance().AddProjectile(new MachineGunBullet(
		body, position, angle,
		stats.GetSize(), velocity, getLifeTime(),
		stats.GetDamage(), bulletGroup
	));
}


