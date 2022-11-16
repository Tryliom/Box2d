#include "manager/WaveManager.h"

#include <iostream>
#include <SFML/Audio/Music.hpp>

#include "Random.h"
#include "manager/AnimationManager.h"
#include "manager/AudioManager.h"
#include "manager/EntityManager.h"

WaveManager::WaveManager()
{
	Reset();
}

void WaveManager::Update(const sf::Time elapsed, Game& game)
{
	_waveTime += elapsed;

	if (!EntityManager::GetInstance().AreEnemiesAlive() || _waveTime >= _waveDuration && _wave % 5 != 0)
	{
		spawnEnemies(game);
	}
}

void WaveManager::Reset()
{
	_wave = 0;
	_waveTime = sf::Time::Zero;
	_waveDuration = sf::seconds(30.f);
}

void WaveManager::spawnEnemies(Game& game)
{
	_wave++;
	_waveTime = sf::Time::Zero;

	EntityManager::GetInstance().RunAway();

	AnimationManager::GetInstance().AddTextAnimation(WaveTextAnimation({ Game::WIDTH / 2.f, Game::HEIGHT / 4.f }, _wave));

	const auto side = static_cast<ScreenSide>(Random::GetInt(0, 3));

	if (_wave % 5 == 0)
	{
		const auto bossEnemies = getBossEnemies();

		for (const auto& enemy : bossEnemies)
		{
			EntityManager::GetInstance().SpawnEnemy(EnemyFactory::createEnemy(enemy, getSpawnPosition(side), game));
		}

		AudioManager::GetInstance().PlayMusic(Music::BOSS_THEME);
	}
	else
	{
		const auto regularEnemies = getRandomRegularEnemies();

		for (const auto& enemy : regularEnemies)
		{
			EntityManager::GetInstance().SpawnEnemy(EnemyFactory::createEnemy(enemy, getSpawnPosition(side), game));
		}

		if ((_wave - 1) % 5 == 0)
		{
			AudioManager::GetInstance().StartMainTheme();
		}
	}
}

sf::Vector2f WaveManager::getSpawnPosition(const ScreenSide side)
{
	if (side == ScreenSide::LEFT)
	{
		return { -100.f, Random::GetFloat(0.f, Game::HEIGHT) };
	}

	if (side == ScreenSide::RIGHT)
	{
		return {Game::WIDTH + 100.f, Random::GetFloat(0.f, Game::HEIGHT)};
	}

	if (side == ScreenSide::TOP)
	{
		return {Random::GetFloat(0.f, Game::WIDTH), -100.f};
	}

	return { Random::GetFloat(0.f, Game::WIDTH), Game::HEIGHT + 100.f };
}

std::vector<EnemyType> WaveManager::getRandomRegularEnemies() const
{
	std::vector<EnemyType> enemies;
	int randomIndex = Random::GetInt(0, REGULAR_ENEMY_COMPOSITION.size() - 1);

	if (_wave == 1)
	{
		randomIndex = 0;
	}

	for (auto& enemy : REGULAR_ENEMY_COMPOSITION[randomIndex])
	{
		for (int i = 0; i < enemy.second; i++)
		{
			enemies.push_back(enemy.first);
		}
	}

	return enemies;
}

std::vector<EnemyType> WaveManager::getBossEnemies() const
{
	std::vector<EnemyType> enemies;

	int index = _wave / 5;

	if (index >= BOSS_ENEMY_COMPOSITION_PER_LEVEL.size())
	{
		index = BOSS_ENEMY_COMPOSITION_PER_LEVEL.size() - 1;
	}

	for (auto& enemy : BOSS_ENEMY_COMPOSITION_PER_LEVEL[index])
	{
		for (int i = 0; i < enemy.second; i++)
		{
			enemies.push_back(enemy.first);
		}
	}

	return enemies;
}
