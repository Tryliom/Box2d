#include "entity/Enemy.h"

#include "Game.h"
#include "manager/EntityManager.h"

Enemy::Enemy(Game& game, sf::Vector2f position, const sf::Texture& texture, float maxHealth,
             Group groupIndex, Stats::EntityStats stats, Stats::WeaponStats weaponStats, const std::vector<Pattern>& patterns) :
	Entity(game, position, texture, maxHealth, stats, groupIndex)
{
	_weaponStats = weaponStats;
	_patterns = patterns;
	_currentPatternTime = sf::Time::Zero;
}

void Enemy::rotateToPlayer(const float angle) const
{
	const sf::Vector2f playerPosition = EntityManager::GetInstance().GetPlayer()->GetPosition();
	const sf::Vector2f direction = playerPosition - GetPosition();
	float flatAngle = Game::RadToDegree(atan2(direction.y, direction.x));

	if (flatAngle < 0.f)
	{
		flatAngle += angle;
	}
	else if (flatAngle > 0.f)
	{
		flatAngle -= angle;
	}

	rotate(flatAngle);
}

void Enemy::stopRotate() const
{
	_body->SetAngularVelocity(0.f);
}

void Enemy::Update(const sf::Time elapsed)
{
	Entity::Update(elapsed);

	_currentPatternTime += elapsed;
	
	const auto action = _patterns[_currentPatternIndex].Action;
	const auto duration = _patterns[_currentPatternIndex].Duration;

	if (_currentPatternTime >= duration && !_weapon->IsCharging())
	{
		_currentPatternIndex = (_currentPatternIndex + 1) % _patterns.size();
		_currentPatternTime = sf::Time::Zero;

		if (_currentPatternIndex == 0)
		{
			onEndCycle();
		}

		_bonusStats = Stats::EntityStats();

		if (action != ActionType::ATTACK && action != ActionType::IDLE)
		{
			// Add bonus movement speed to the enemy
			_bonusStats = Stats::EntityStats{
				.SpeedPercentage = 1.f,
				.RotationSpeed = 5.f,
			};
		}
	}

	// If the enemy is out the screen and is not running away, make it move to the player
	if (action == ActionType::MOVE_TO_PLAYER ||
		Game::IsOutOfScreen(GetPosition()) && action != ActionType::RUN_AWAY)
	{
		rotateToPlayer();
		Move(elapsed);
	}
	else if (action == ActionType::RUN_AWAY)
	{
		Move(elapsed);
		stopRotate();

		AddBonusStats(Stats::EntityStats{
				.SpeedPercentage = 0.5f * elapsed.asSeconds()
			});

		// If out of screen, destroy
		const float x = GetPosition().x - _shape.getSize().x / 2.f;
		const float y = GetPosition().y - _shape.getSize().y / 2.f;

		if (Game::IsOutOfScreen(sf::Vector2f(x, y)))
		{
			_health = 0.f;
		}
	}
	else if (action == ActionType::ATTACK)
	{
		rotateToPlayer();
		ChargeWeapon();
	}
	else if (action == ActionType::MOVE_AROUND_PLAYER)
	{
		rotateToPlayer(45.f);
		Move(elapsed);
	}
	else if (action == ActionType::ROTATE)
	{
		rotateToPlayer();
	}

	if (_weapon->IsCharging() && action != ActionType::ATTACK)
	{
		_weapon->StopCharging();
	}
}

void Enemy::RunAway()
{
	_currentPatternIndex = 0;
	_currentPatternTime = sf::Time::Zero;
	_patterns = { { ActionType::RUN_AWAY, sf::seconds(30.f) } };

	StopChargingWeapon();
}
