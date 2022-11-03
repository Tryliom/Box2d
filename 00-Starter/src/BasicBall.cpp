#include "BasicBall.h"

#include "Game.h"
#include "Random.h"

BasicBall::BasicBall(b2Body* body, const sf::Vector2f position) : DrawableObject(body, position)
{
	// Set up the fixture
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = Random::GetFloat(0.5f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = Random::GetFloat(10.f, 50.f);
	fixtureDef.restitution = Random::GetFloat(0.1f, 1.f);
	fixtureDef.friction = Random::GetFloat(0.1f, 1.f);

	_body->CreateFixture(&fixtureDef);

	_shape.setRadius(Game::MeterToPixel(dynamicBox.m_radius));
	_shape.setOrigin(_shape.getRadius(), _shape.getRadius());
	_shape.setFillColor(sf::Color::White);
	_shape.setPosition(position);
}

void BasicBall::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape);
}

void BasicBall::Update(sf::Time elapsed)
{
	_shape.setPosition(Game::MeterToPixel(_body->GetPosition()));
}
