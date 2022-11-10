#include "entity/Enemy.h"

#include "Game.h"

Enemy::Enemy(Game& game, sf::Vector2f position, const sf::Texture& texture, float health, float maxHealth,
	Group groupIndex, Stats::EntityStats stats, Stats::WeaponStats weaponStats, const std::vector<Pattern>& patterns) :
	Entity(game, position, texture, health, maxHealth, stats, groupIndex)
{
	_weaponStats = weaponStats;
	_patterns = patterns;
	_currentPatternTime = sf::Time::Zero;
}

void Enemy::rotateToPlayer(const float angle) const
{
	const sf::Vector2f playerPosition = _game.GetPlayer().GetPosition();
	const sf::Vector2f direction = playerPosition - GetPosition();
	float flatAngle = Game::RadToDegree(atan2(direction.y, direction.x));

	//TODO: Apply angle offset

	rotate(flatAngle);
}

void Enemy::Update(const sf::Time elapsed)
{
	Entity::Update(elapsed);

	_currentPatternTime += elapsed;

	if (_currentPatternTime >= _patterns[_currentPatternIndex].Duration)
	{
		_currentPatternIndex = (_currentPatternIndex + 1) % _patterns.size();
		_currentPatternTime = sf::Time::Zero;

		if (_currentPatternIndex == 0)
		{
			onEndCycle();
		}

		StopChargingWeapon();
	}

	// If the enemy is out the screen and is not running away, make it move to the player
	if (_patterns[_currentPatternIndex].Action == ActionType::MOVE_TO_PLAYER || 
		Game::IsOutOfScreen(GetPosition()) && _patterns[_currentPatternIndex].Action != ActionType::RUN_AWAY)
	{
		rotateToPlayer();
		Move();
	}
	else if (_patterns[_currentPatternIndex].Action == ActionType::RUN_AWAY_FROM_PLAYER || _patterns[_currentPatternIndex].Action == ActionType::RUN_AWAY)
	{
		rotateToPlayer(180.f);
		Move();

		if (_patterns[_currentPatternIndex].Action == ActionType::RUN_AWAY)
		{
			// If out of screen, destroy
			const float x = GetPosition().x + _shape.getSize().x / 2.f;
			const float y = GetPosition().y + _shape.getSize().y / 2.f;

			if (x < 0.f || x > _game.GetWindow().getSize().x || y < 0.f || y > _game.GetWindow().getSize().y)
			{
				_health = 0.f;
			}
		}
	}
	else if (_patterns[_currentPatternIndex].Action == ActionType::ATTACK)
	{
		//TODO: Check if the enemy has the time to do an attack or force it to finish his attack

		rotateToPlayer();
		ChargeWeapon();
	}
	else if (_patterns[_currentPatternIndex].Action == ActionType::MOVE_AROUND_PLAYER)
	{
		rotateToPlayer(90.f);
		Move();
	}
}
