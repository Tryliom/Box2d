#pragma once
#include "entity/Entity.h"

enum class ActionType
{
	IDLE,
	MOVE_TO_PLAYER,
	MOVE_AROUND_PLAYER,
	RUN_AWAY,
	ATTACK,
	ROTATE
};

struct Pattern
{
	ActionType Action{ ActionType::IDLE };
	sf::Time Duration{ sf::Time::Zero };
};

class Enemy : public Entity
{
public:
	Enemy(
		Game& game, sf::Vector2f position, const sf::Texture& texture,
		float maxHealth, int xp,
		Group groupIndex, Stats::EntityStats stats, Stats::WeaponStats weaponStats, const std::vector<Pattern>& patterns
	);

protected:
	int _xp;

	std::vector<Pattern> _patterns;
	sf::Time _currentPatternTime;
	size_t _currentPatternIndex{ 0 };

	bool _killedByPlayer{ true };

	virtual void onEndCycle() {}
	void rotateToPlayer(float angle = 0.f) const;
	void stopRotate() const;

public:
	void Update(sf::Time elapsed) override;

	void RunAway();

	int GetXp() const;
	bool IsKilledByPlayer() const;
};