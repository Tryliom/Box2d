#include "factory/WeaponFactory.h"

#include "entity/Entity.h"
#include "weapon/weapons/Canon.h"
#include "weapon/weapons/MachineGun.h"
#include "weapon/weapons/Sniper.h"

void WeaponFactory::AssignWeapon(const WeaponType type, Entity* entity)
{
	if (type == WeaponType::MACHINE_GUN)
	{
		entity->ChangeWeapon(new MachineGun(entity->GetWeaponStats()));
	}
	else if (type == WeaponType::SNIPER)
	{
		entity->ChangeWeapon(new Sniper(entity->GetWeaponStats()));
	}
	else if (type == WeaponType::CANON)
	{
		entity->ChangeWeapon(new Canon(entity->GetWeaponStats()));
	}
}

std::string WeaponFactory::GetWeaponName(WeaponType type)
{
	if (type == WeaponType::MACHINE_GUN)
	{
		return "Machine gun";
	}
	else if (type == WeaponType::SNIPER)
	{
		return "Sniper";
	}
	else if (type == WeaponType::CANON)
	{
		return "Canon";
	}

	return "";
}
