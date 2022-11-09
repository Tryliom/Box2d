#include "weapon/weapons/MachineGun.h"

#include "projectile/bullets/RegularBullet.h"

MachineGun::MachineGun(Stats::WeaponStats& userStats) :
	Weapon(Stats::WeaponStats{
		.Damage = 5.f,
		.Speed = 120.f,
		.Spread = 5.f,
		.Range = 500.f,
		.BulletsPerShot = 3,
		.Cooldown = 0.3f,
		.Size = 0.75f
	}, userStats)
{

}

void MachineGun::shootBullet(b2Body* body, const sf::Vector2f position, const float angle, const b2Vec2 velocity,
	const Group bulletGroup)
{
	const Stats::WeaponStats stats = getTotalStats();

	_bullets.push_back(new RegularBullet(
		body, position, angle,
		stats.GetSize(), velocity, getLifeTime(),
		stats.GetDamage(), bulletGroup
	));
}


