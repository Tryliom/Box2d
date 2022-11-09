#pragma once
#include "projectile/Projectile.h"

class Spark final : public Projectile
{
public:
	Spark(b2Body* body, sf::Vector2f position, float angle, float size, b2Vec2 velocity, float damage, Group group);
	
	void Update(sf::Time elapsed) override;
};