#pragma once
#include "projectile/Projectile.h"

// This is the trail that the player leaves behind, stuck to the back of the ship
class Tail final : public Projectile
{
public:
	Tail(b2Body* body, sf::Vector2f position, float angle, float damage);

	void Update(sf::Time elapsed) override;
};