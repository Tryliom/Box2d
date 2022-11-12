#pragma once
#include "projectile/Projectile.h"

class RegularBullet final : public Projectile
{
public:
	RegularBullet(b2Body* body, sf::Vector2f position,
		float angle, float size, b2Vec2 velocity, sf::Time lifeTime,
		float damage, Group groupIndex, bool trail = false
	);

	void Update(sf::Time elapsed) override;
};