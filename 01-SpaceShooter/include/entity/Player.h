#pragma once
#include "animation/Tail.h"
#include "entity/Entity.h"

constexpr float TAIL_COOLDOWN = 0.1f;

class Player final : public Entity
{
public:
	Player(Game& game, sf::Vector2f position);

protected:
	std::list<Tail> _tails;
	sf::Time _tailCooldown;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Get trail position at the bottom of the ship that change with the rotation
	sf::Vector2f getTrailPosition() const;

public:
	void Update(sf::Time elapsed) override;
	void Move() override;
};
