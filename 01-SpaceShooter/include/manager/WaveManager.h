#pragma once
#include <SFML/Graphics.hpp>

#include "factory/EnemyFactory.h"

class Game;

enum class ScreenSide
{
	LEFT, RIGHT, TOP, BOTTOM
};

const std::vector<std::vector<std::pair<EnemyType, int>>> REGULAR_ENEMY_COMPOSITION = {
	{{EnemyType::CAMPER, 5}},
	{{EnemyType::CAMPER, 3}, {EnemyType::ANGEL, 2}},
	{{EnemyType::ANGEL, 3}}
};

const std::vector<std::vector<std::pair<EnemyType, int>>> BOSS_ENEMY_COMPOSITION_PER_LEVEL = {
	{{EnemyType::IMPERATOR, 1}},
	{{EnemyType::IMPERATOR, 1}, {EnemyType::CAMPER, 5}},
	{{EnemyType::IMPERATOR, 1}, {EnemyType::ANGEL, 2}, {EnemyType::CAMPER, 3}},
	{{EnemyType::IMPERATOR, 2}, {EnemyType::ANGEL, 5}}
};

class WaveManager final
{
public:
	WaveManager();

	void Update(sf::Time elapsed, Game& game);
	void Reset();

private:
	int _wave{ 0 };
	sf::Time _waveTime{ sf::Time::Zero };
	sf::Time _waveDuration{ sf::seconds(30.f) };

	void spawnEnemies(Game& game);
	static sf::Vector2f getSpawnPosition(ScreenSide side);
	[[nodiscard]] std::vector<EnemyType> getRandomRegularEnemies() const;
	[[nodiscard]] std::vector<EnemyType> getBossEnemies() const;
};
