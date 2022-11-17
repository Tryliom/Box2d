#pragma once
#include "weapon/Weapon.h"

enum class WeaponType : int
{
	MACHINE_GUN = 0, SNIPER, CANON, SHOT_GUN
};

namespace WeaponFactory
{
	void AssignWeapon(WeaponType type, Entity* entity);
	std::string GetWeaponName(WeaponType type);
}
