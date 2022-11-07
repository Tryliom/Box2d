#pragma once
#include "weapon/Weapon.h"

// Most basic weapon, shoot a single bullet after a short charge
class Canon : public Weapon
{
public:
	Canon();

protected:
	sf::Vector2f getFrontPosition(const Entity& entity) const;

public:
	void StartCharging(Entity entity) override;
	void Shoot(Entity entity, Group bulletGroup) override;
};