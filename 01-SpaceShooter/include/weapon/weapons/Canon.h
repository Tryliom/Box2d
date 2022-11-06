#pragma once
#include "weapon/Weapon.h"

// Most basic weapon, shoot a single bullet after a short charge
class Canon : public Weapon
{
public:
	Canon();

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void StartCharging(b2Body* user, sf::Vector2f size) override;

	void Shoot(b2Body* user, Group bulletGroup) override;
};