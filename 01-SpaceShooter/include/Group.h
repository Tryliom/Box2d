#pragma once
#include <SFML/Graphics/Color.hpp>

enum class Group
{
	UNKNOWN,
	PLAYER,
	ENEMY,
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE,
	XP
};

inline sf::Color GetColor(const Group group)
{
	if (group == Group::ENEMY)
	{
		return { 238, 102, 102 };
	}

	if (group == Group::ENEMY_PROJECTILE)
	{
		return { 231, 87, 36 };
	}

	if (group == Group::PLAYER)
	{
		return { 138, 224, 232 };
	}

	if (group == Group::PLAYER_PROJECTILE)
	{
		return { 46, 186, 225 };
	}

	if (group == Group::XP)
	{
		return { 134, 238, 102 };
	}
	
	return sf::Color::Black;
}