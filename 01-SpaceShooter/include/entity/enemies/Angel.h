#pragma once
#include "entity/Enemy.h"

class Angel final : public Enemy
{
public:
	Angel(Game& game, sf::Vector2f position);
};
