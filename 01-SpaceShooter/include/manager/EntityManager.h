#pragma once
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "entity/Enemy.h"
#include "entity/Player.h"

class EntityManager final : public sf::Drawable
{
private:
	EntityManager();

	std::list<Enemy*> _enemies;
	Player* _player;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;

	static EntityManager& GetInstance()
	{
		static EntityManager instance;
		return instance;
	}

	void Update(sf::Time elapsed, GameState state);
	void CheckInputs(sf::Event event) const;

	void SpawnEnemy(Enemy* entity);
	void Restart(Game& game);
	void RunAway() const;
	void EndGame() const;

	[[nodiscard]] bool IsPlayerAlive() const;
	[[nodiscard]] bool AreEnemiesAlive() const;

	[[nodiscard]] Player* GetPlayer() const { return _player; }
};
