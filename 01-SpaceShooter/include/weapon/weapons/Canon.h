#pragma once
#include "weapon/Weapon.h"

// Most basic weapon, shoot a big bullet after a medium charge
class Canon final : public Weapon
{
public:
	explicit Canon(Entity* user);

protected:
	void shootBullet(b2Body* body, const sf::Vector2f position, const float angle, const b2Vec2 velocity, const Group bulletGroup) override;
};