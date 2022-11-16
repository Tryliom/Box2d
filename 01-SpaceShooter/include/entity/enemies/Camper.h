#pragma once
#include "entity/Enemy.h"

class Camper final : public Enemy
{
public:
	Camper(Game& game, sf::Vector2f position, int level);
};