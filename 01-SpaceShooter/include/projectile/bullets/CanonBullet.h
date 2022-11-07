#pragma once
#include "projectile/Projectile.h"

class CanonBullet final : public Projectile
{
public:
	CanonBullet(b2Body* body, sf::Vector2f position,
		float angle, b2Vec2 velocity, sf::Time lifeTime,
		float damage, bool canPierce, Group groupIndex
	);

	void Update(sf::Time elapsed) override;
};