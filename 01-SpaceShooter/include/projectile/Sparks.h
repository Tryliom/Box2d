#pragma once
#include "projectile/Projectile.h"

class Sparks final : public Projectile
{
public:
	Sparks(b2Body* body, sf::Vector2f position, float angle, b2Vec2 velocity, float damagePerSeconds);
	
	void Update(sf::Time elapsed) override;
};