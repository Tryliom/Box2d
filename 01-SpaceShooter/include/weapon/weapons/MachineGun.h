#pragma once
#include "weapon/Weapon.h"

// Shoot a lot of small bullets
class MachineGun final : public Weapon
{
public:
	explicit MachineGun(Entity* user);

protected:
	void shootBullet(b2Body* body, const sf::Vector2f position, const float angle, const b2Vec2 velocity, const Group bulletGroup) override;
};