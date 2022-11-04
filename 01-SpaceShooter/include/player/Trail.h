#pragma once
#include "DrawableObject.h"

// This is the trail that the player leaves behind, stuck to the back of the ship
class Trail final : public DrawableObject
{
public:
	Trail(b2Body* body, sf::Vector2f position, float angle);

protected:
	sf::Sprite _sprite;

	sf::Time _lifeTime;
	sf::Time _currentLifeTime;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Update(sf::Time elapsed) override;
	void UpdatePosition(sf::Vector2f position, float rad) const;

	bool IsDead() const { return _currentLifeTime >= _lifeTime; }
};