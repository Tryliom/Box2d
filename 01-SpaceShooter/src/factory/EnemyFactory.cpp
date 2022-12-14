#include "factory/EnemyFactory.h"

#include "entity/enemies/Angel.h"
#include "entity/enemies/Camper.h"
#include "entity/enemies/Imperator.h"

Enemy* EnemyFactory::createEnemy(const EnemyType type, const sf::Vector2f& position, Game& game, const int level)
{
	if (type == EnemyType::CAMPER)
	{
		return new Camper(game, position, level);
	}
	else if (type == EnemyType::ANGEL)
	{
		return new Angel(game, position, level);
	}
	else if (type == EnemyType::IMPERATOR)
	{
		return new Imperator(game, position, level);
	}
	else
	{
		return nullptr;
	}
}
