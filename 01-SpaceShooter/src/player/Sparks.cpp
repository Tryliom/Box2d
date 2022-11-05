#include "player/Sparks.h"

#include "Assets.h"
#include "Game.h"

Sparks::Sparks(b2Body* body, const sf::Vector2f position, const float angle, const b2Vec2 velocity, const float damagePerSeconds) : DrawableObject(body, position)
{
	const sf::Texture& texture = Assets::GetInstance().GetTexture(Texture::SPARKS);

	_sprite.setTexture(texture);
	_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
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
	_body->SetType(b2_dynamicBody);

	_body->SetLinearVelocity(velocity);

	// Ignore the collision between the player and the sparks
	_body->GetFixtureList()->SetSensor(true);

	_lifeTime = sf::seconds(0.5f);
	_currentLifeTime = sf::Time::Zero;

	_damagePerSecond = damagePerSeconds;
}

void Sparks::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void Sparks::Update(const sf::Time elapsed)
{
	_currentLifeTime += elapsed;

	// Make the sparks texture more transparent over time
	_sprite.setColor(sf::Color(255, 255, 255, 255 - (255 * _currentLifeTime.asSeconds() / _lifeTime.asSeconds())));

	// Make the sparks smaller over time
	_sprite.setScale(2.f - 1.5f * _currentLifeTime.asSeconds() / _lifeTime.asSeconds(), 2.f - 1.5f * _currentLifeTime.asSeconds() / _lifeTime.asSeconds());

	_sprite.setPosition(Game::MeterToPixel(_body->GetPosition()));
	_sprite.setRotation(Game::RadToDegree(_body->GetAngle()));
}
