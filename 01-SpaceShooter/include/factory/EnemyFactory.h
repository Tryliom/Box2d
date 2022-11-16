#pragma once
#include "entity/Enemy.h"

enum class EnemyType
{
	CAMPER, ANGEL, IMPERATOR
};

namespace EnemyFactory
{
	Enemy* createEnemy(EnemyType type, const sf::Vector2f& position, Game& game, int level);
}