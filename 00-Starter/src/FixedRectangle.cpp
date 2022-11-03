#include "FixedRectangle.h"

#include "Game.h"

FixedRectangle::FixedRectangle(b2Body* body, sf::Vector2f position, sf::Vector2f size, sf::Color color, float angle, float angleSpeed)
	: DrawableObject(body, position)
{
	b2PolygonShape shape;
	shape.SetAsBox(Game::PixelToMeter(size.x / 2.f), Game::PixelToMeter(size.y / 2.f));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	_body->CreateFixture(&fixtureDef);

	// Make it fixed
	_body->SetType(b2_staticBody);

	_shape.setSize(size);
	_shape.setPosition(position);
	_shape.setOrigin(size / 2.0f);
	_shape.setFillColor(color);
	_shape.setRotation(angle);

	_body->SetTransform(Game::PixelToMeter(position), angle * b2_pi / -180.0f);

	_angleSpeed = angleSpeed;
}

void FixedRectangle::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_shape, states);
}

void FixedRectangle::Update(sf::Time elapsed)
{
	_shape.setPosition(Game::MeterToPixel(_body->GetPosition()));
	
	// Update the angle based of the elapsed time
	float angle = _shape.getRotation() + elapsed.asSeconds() * _angleSpeed;

	// Make sure the angle is between 0 and 360
	if (angle > 360.0f)
	{
		angle -= 360.0f;
	}

	_shape.setRotation(angle);

	// Update the body's angle
	_body->SetTransform(_body->GetPosition(), angle * b2_pi / -180.0f);
}