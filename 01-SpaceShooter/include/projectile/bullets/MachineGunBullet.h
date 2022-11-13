#pragma once
#include "projectile/Projectile.h"

class MachineGunBullet final : public Projectile
{
public:
	MachineGunBullet(b2Body* body, sf::Vector2f position,
		float angle, float size, b2Vec2 velocity, sf::Time lifeTime,
		float damage, Group groupIndex, bool trail = false
	);
};