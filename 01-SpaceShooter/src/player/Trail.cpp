#include "player/Trail.h"

#include "Assets.h"
#include "Game.h"

#include "box2d/b2_chain_shape.h"

Trail::Trail(b2Body* body, const sf::Vector2f position, const float angle) : DrawableObject(body, position)
{
	const sf::Texture texture = Assets::GetInstance().GetTexture(Texture::TRAIL);

	_sprite.setTexture(texture);
	_sprite.setPosition(position);
	_sprite.setRotation(angle);

	b2ChainShape chainShape;
	b2Vec2 vertices[4];

	vertices[0].Set(-Game::PixelToMeter(texture.getSize().x / 2.f), -Game::PixelToMeter(texture.getSize().y / 2.f));
	vertices[1].Set(Game::PixelToMeter(texture.getSize().x / 2.f), -Game::PixelToMeter(texture.getSize().y / 2.f));
	vertices[2].Set(Game::PixelToMeter(texture.getSize().x / 2.f), Game::PixelToMeter(texture.getSize().y / 2.f));
	vertices[3].Set(-Game::PixelToMeter(texture.getSize().x / 2.f), Game::PixelToMeter(texture.getSize().y / 2.f));

	chainShape.CreateLoop(vertices, 4);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &chainShape;
	fixtureDef.density = 1.f;
	fixtureDef.restitution = 0.1f;
	fixtureDef.friction = 0.1f;

	_body->CreateFixture(&fixtureDef);

	_body->SetTransform(Game::PixelToMeter(position), Game::sfAngleToB2Angle(_sprite.getRotation()));
}

void Trail::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void Trail::Update(sf::Time elapsed)
{
	// Make the trail texture more transparent over time
	_sprite.setColor(sf::Color(255, 255, 255, 255 - (255 * _currentLifeTime.asSeconds() / _lifeTime.asSeconds())));

	// Make the trail bigger over time
	_sprite.setScale(1 + _currentLifeTime.asSeconds() / _lifeTime.asSeconds(), 1 + _currentLifeTime.asSeconds() / _lifeTime.asSeconds());

	_sprite.setPosition(Game::MeterToPixel(_body->GetPosition()));
	_sprite.setRotation(Game::b2AngleToSfAngle(_body->GetAngle()));
}

void Trail::UpdatePosition(const sf::Vector2f position, const float b2Angle) const
{
	_body->SetTransform(Game::PixelToMeter(position), b2Angle);
}
