#pragma once
#include "DrawableObject.h"

class BasicBall : public DrawableObject
{
public:
	BasicBall(b2Body* body, sf::Vector2f position);

protected:
	sf::CircleShape _shape;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	virtual void Update(sf::Time elapsed) override;
};