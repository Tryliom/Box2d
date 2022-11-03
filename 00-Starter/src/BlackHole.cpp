#include "BlackHole.h"

BlackHole::BlackHole(b2Body* body, const sf::Vector2f position) : BasicBall(body, position)
{
	_shape.setFillColor(sf::Color::Black);
	_shape.setOutlineColor(sf::Color::White);
	_shape.setOutlineThickness(-1.0f);

	// Set the body static
	_body->SetType(b2_staticBody);
}
