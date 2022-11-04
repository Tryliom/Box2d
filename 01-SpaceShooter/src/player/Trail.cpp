#include "player/Trail.h"

#include "Assets.h"
#include "Game.h"

#include "box2d/b2_chain_shape.h"

Trail::Trail(b2Body* body, const sf::Vector2f position, const float angle) : DrawableObject(body, position)
{
	const sf::Texture& texture = Assets::GetInstance().GetTexture(Texture::TRAIL);

	_sprite.setTexture(texture);
	_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	_sprite.setPosition(position);
	_sprite.setRotation(angle);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(Game::PixelToMeter(_sprite.getGlobalBounds().width / 2.f), Game::PixelToMeter(_sprite.getGlobalBounds().height / 2.f));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.f;
	fixtureDef.restitution = 0.f;
	fixtureDef.friction = 0.f;

	_body->CreateFixture(&fixtureDef);

	_body->SetTransform(Game::PixelToMeter(position), Game::DegreeToRad(_sprite.getRotation()));

	// Ignore the collision between the player and the trail
	_body->GetFixtureList()->SetSensor(true);

	_lifeTime = sf::seconds(0.5f);
}

void Trail::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void Trail::Update(const sf::Time elapsed)
{
	_currentLifeTime += elapsed;

	// Make the trail texture more transparent over time
	_sprite.setColor(sf::Color(255, 255, 255, 255 - (255 * _currentLifeTime.asSeconds() / _lifeTime.asSeconds())));

	// Make the trail bigger over time
	//_sprite.setScale(1 + _currentLifeTime.asSeconds() / _lifeTime.asSeconds(), 1 + _currentLifeTime.asSeconds() / _lifeTime.asSeconds());

	_sprite.setPosition(Game::MeterToPixel(_body->GetPosition()));
	_sprite.setRotation(Game::RadToDegree(_body->GetAngle()));
}

void Trail::UpdatePosition(const sf::Vector2f position, const float rad) const
{
	_body->SetTransform(Game::PixelToMeter(position), rad);
}
