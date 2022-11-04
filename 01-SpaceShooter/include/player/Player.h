#pragma once
#include "Game.h"
#include "Trail.h"

constexpr float TRAIL_COOLDOWN = 0.1f;

class Player final : public DrawableObject
{
public:
	Player(Game& game, sf::Vector2f position);

protected:
	int _health;
	int _maxHealth;

	float _speed;
	float _rotationSpeed;
	float _maxSpeed;
	int _sparksPerSecond;

	sf::RectangleShape _shape;

	std::vector<Trail> _trails;
	sf::Time _trailCooldown;

	Game& _game;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Update(sf::Time elapsed) override;

	void Move();

	sf::Vector2f GetPosition() const;
	void SetPosition(sf::Vector2f position);
};
