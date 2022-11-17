#pragma once
#include "weapon/Weapon.h"

class ShotGun final : public Weapon
{
public:
	explicit ShotGun(Entity* user);

protected:
	void shootBullet(b2Body* body, const sf::Vector2f position, const float angle, const b2Vec2 velocity, const Group bulletGroup) override;
};