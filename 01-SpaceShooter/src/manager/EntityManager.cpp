#include "manager/EntityManager.h"

#include "Game.h"

EntityManager::EntityManager()
{
	_enemies = {};
	_player = nullptr;
}

void EntityManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto* entity : _enemies)
	{
		target.draw(*entity);
	}

	if (_player != nullptr && _player->IsAlive())
	{
		target.draw(*_player);
	}
}

void EntityManager::Update(const sf::Time elapsed, const GameState state)
{
	if (_player != nullptr)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && state == GameState::PLAYING && _player->IsAlive())
		{
			_player->Move(elapsed);
		}

		if (state != GameState::UPGRADE_CHOICE)
		{
			_player->Update(elapsed);

			// If the player go out of the screen, teleport him to the other side
			if (_player->GetPosition().x < 0)
			{
				_player->SetPosition(sf::Vector2f(Game::WIDTH, _player->GetPosition().y));
			}
			else if (_player->GetPosition().x > Game::WIDTH)
			{
				_player->SetPosition(sf::Vector2f(0, _player->GetPosition().y));
			}
			else if (_player->GetPosition().y < 0)
			{
				_player->SetPosition(sf::Vector2f(_player->GetPosition().x, Game::HEIGHT));
			}
			else if (_player->GetPosition().y > Game::HEIGHT)
			{
				_player->SetPosition(sf::Vector2f(_player->GetPosition().x, 0));
			}
		}
	}

	// Remove enemies that are dead
	for (auto it = _enemies.begin(); it != _enemies.end();)
	{
		(*it)->Update(elapsed);

		if ((*it)->IsDead())
		{
			(*it)->GetBody()->GetWorld()->DestroyBody((*it)->GetBody());

			it = _enemies.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void EntityManager::CheckInputs(const sf::Event event) const
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
	{
		_player->ChargeWeapon();
	}

	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
	{
		_player->StopChargingWeapon();
	}
}

void EntityManager::SpawnEnemy(Enemy* entity)
{
	_enemies.emplace_back(entity);
}

void EntityManager::Restart(Game& game)
{
	_player = new Player(game);

	// Remove all enemies from the world and the list
	for (auto it = _enemies.begin(); it != _enemies.end();)
	{
		(*it)->GetBody()->GetWorld()->DestroyBody((*it)->GetBody());

		it = _enemies.erase(it);
	}
}

void EntityManager::RunAway() const
{
	for (const auto entity : _enemies)
	{
		entity->RunAway();
	}
}

void EntityManager::EndGame() const
{
	_player->StopChargingWeapon();

	RunAway();
}

bool EntityManager::IsPlayerAlive() const
{
	return _player != nullptr && !_player->IsDead();
}

bool EntityManager::AreEnemiesAlive() const
{
	return !_enemies.empty();
}
