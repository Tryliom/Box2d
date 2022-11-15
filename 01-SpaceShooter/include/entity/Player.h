#pragma once
#include "animation/Tail.h"
#include "entity/Entity.h"

constexpr float TAIL_COOLDOWN = 0.1f;

class Player final : public Entity
{
public:
	explicit Player(Game& game);

protected:
	std::list<Tail> _tails;
	sf::Time _tailCooldown;

	bool _copilot = true;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Get tail position at the bottom of the ship that change with the rotation
	sf::Vector2f getTailPosition() const;

public:
	void Update(sf::Time elapsed) override;
	void Move(sf::Time elapsed) override;

	void TakeControl();
	bool IsAlive() const;
};
