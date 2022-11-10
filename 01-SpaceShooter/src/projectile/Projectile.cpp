#include "projectile/Projectile.h"

#include <iostream>

#include "Game.h"

Projectile::Projectile(b2Body* body, const sf::Vector2f position, 
						const sf::Texture& texture, ShapeType shapeType,
						const float angle, float size, const b2Vec2 velocity, const sf::Time lifeTime,
						const float damage, const bool canPierce, const Group groupIndex) :
	DrawableObject(body, position)
{
	_lifeTime = lifeTime;
	_currentLifeTime = sf::Time::Zero;
	_damage = damage;
	_canPierce = canPierce;
	_groupIndex = groupIndex;

	_sprite.setTexture(texture);
	_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	_sprite.setRotation(angle);
	_sprite.setScale(size, size);
	_sprite.setPosition(position);

	b2FixtureDef fixtureDef;
	b2PolygonShape dynamicBox;
	b2CircleShape circleShape;

	if (shapeType == ShapeType::RECTANGLE)
	{
		dynamicBox.SetAsBox(Game::PixelToMeter(_sprite.getGlobalBounds().width / 2.f), Game::PixelToMeter(_sprite.getGlobalBounds().height / 2.f));

		fixtureDef.shape = &dynamicBox;
	}
	else
	{
		circleShape.m_radius = Game::PixelToMeter(_sprite.getGlobalBounds().width / 2.f);

		fixtureDef.shape = &circleShape;
	}

	fixtureDef.density = 0.f;
	fixtureDef.restitution = 0.f;
	fixtureDef.friction = 0.f;
	fixtureDef.filter.groupIndex = static_cast<int16>(_groupIndex);
	fixtureDef.isSensor = true;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

	_body->CreateFixture(&fixtureDef);

	_body->SetTransform(Game::PixelToMeter(position), Game::DegreeToRad(_sprite.getRotation()));
	_body->SetType(b2_dynamicBody);
	_body->SetLinearVelocity(velocity);
}

void Projectile::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void Projectile::Update(const sf::Time elapsed)
{
	_currentLifeTime += elapsed;

	_sprite.setPosition(Game::MeterToPixel(_body->GetPosition()));
	_sprite.setRotation(Game::RadToDegree(_body->GetAngle()));

	const sf::Uint8 alpha = 255 - (255 * _currentLifeTime.asSeconds() / _lifeTime.asSeconds());

	sf::Color color = GetColor(_groupIndex);
	color.a = alpha;

	_sprite.setColor(color);
}

void Projectile::OnImpact()
{
	if (!_canPierce)
	{
		_currentLifeTime = _lifeTime;
	}
}
