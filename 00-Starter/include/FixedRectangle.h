#pragma once
#include "DrawableObject.h"

class FixedRectangle : public DrawableObject
{
public:
	FixedRectangle(b2Body* body, sf::Vector2f position, sf::Vector2f size, sf::Color color, float angle = 0.0f, float angleSpeed = 0.0f);

private:
	sf::RectangleShape _shape;
	float _angleSpeed;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Update(sf::Time elapsed) override;
};