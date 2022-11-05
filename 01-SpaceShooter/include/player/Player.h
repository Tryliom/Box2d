#pragma once
#include "Trail.h"

class Game;

constexpr float TRAIL_COOLDOWN = 0.1f;

class Player final : public DrawableObject
{
public:
	Player(Game& game, sf::Vector2f position);

protected:
	float _health;
	float _maxHealth;
	float _healthRegeneration;

	float _speed;
	float _rotationSpeed;
	float _maxSpeed;
	int _sparksPerSecond;

	sf::RectangleShape _shape;

	std::vector<Trail> _trails;
	sf::Time _trailCooldown;

	Game& _game;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Returns the nearest angle to the given angle
	float getNearestAngle(float angle) const;

	// Get trail position at the bottom of the ship that change with the rotation
	sf::Vector2f getTrailPosition() const;
public:
	void Update(sf::Time elapsed) override;
	void Move();

	sf::Vector2f GetPosition() const;
	void SetPosition(sf::Vector2f position);

	bool IsDead() const { return _health <= 0.f; }
	void TakeDamage(float damage);
};
