#pragma once
#include "weapon/Weapon.h"

// Most basic weapon, shoot a big bullet after a medium charge
class Canon : public Weapon
{
public:
	Canon(Stats::WeaponStats& userStats);

protected:
	sf::Vector2f getFrontPosition(Entity* entity) const;

public:
	void StartCharging(Entity* entity) override;
	void Shoot(Entity* entity, Group bulletGroup) override;
};