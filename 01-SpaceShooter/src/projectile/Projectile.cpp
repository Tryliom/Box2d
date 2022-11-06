#include "projectile/Projectile.h"

#include "Game.h"

Projectile::Projectile(b2Body* body, const sf::Vector2f position, const sf::Texture& texture,
                       const float angle, const b2Vec2 velocity, const sf::Time lifeTime,
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

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(Game::PixelToMeter(_sprite.getGlobalBounds().width / 2.f), Game::PixelToMeter(_sprite.getGlobalBounds().height / 2.f));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.f;
	fixtureDef.restitution = 0.f;
	fixtureDef.friction = 0.f;
	fixtureDef.isSensor = true;
	fixtureDef.filter.groupIndex = static_cast<int16>(_groupIndex);

	_body->CreateFixture(&fixtureDef);

	_body->SetTransform(Game::PixelToMeter(position), Game::DegreeToRad(_sprite.getRotation()));
	_body->SetType(b2_dynamicBody);
	_body->SetLinearVelocity(velocity);
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void Projectile::Update(const sf::Time elapsed)
{
	_currentLifeTime += elapsed;

	_sprite.setPosition(Game::MeterToPixel(_body->GetPosition()));
	_sprite.setRotation(Game::RadToDegree(_body->GetAngle()));
}

void Projectile::OnImpact()
{
	if (!_canPierce)
	{
		_currentLifeTime = _lifeTime;
	}
}
