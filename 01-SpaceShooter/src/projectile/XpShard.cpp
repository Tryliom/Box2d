#include "projectile/XpShard.h"

#include <iostream>

#include "Assets.h"
#include "Game.h"

XpShard::XpShard(b2Body* body, const sf::Vector2f position, const int xp) :
	DrawableObject(body, position)
{
	_xp = xp;

	const sf::Texture& texture = Assets::GetInstance().GetTexture(Texture::XP_SHARD);

	_sprite.setTexture(texture);
	_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	_sprite.setRotation(0.f);
	_sprite.setPosition(position);

	b2FixtureDef fixtureDef;
	b2CircleShape circleShape;
	circleShape.m_radius = Game::PixelToMeter(_sprite.getGlobalBounds().width / 2.f);
	fixtureDef.shape = &circleShape;

	fixtureDef.density = 0.f;
	fixtureDef.restitution = 0.f;
	fixtureDef.friction = 0.f;
	fixtureDef.filter.groupIndex = static_cast<int16>(Group::XP);
	fixtureDef.isSensor = true;
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

	_body->CreateFixture(&fixtureDef);

	_body->SetTransform(Game::PixelToMeter(position), Game::DegreeToRad(_sprite.getRotation()));
	_body->SetType(b2_dynamicBody);
}

void XpShard::Update(const sf::Time elapsed)
{
	_sprite.setPosition(Game::MeterToPixel(_body->GetPosition()));
	_sprite.setRotation(_sprite.getRotation() + 720.f * elapsed.asSeconds());
}

void XpShard::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

bool XpShard::IsPickedUp() const
{
	return _pickedUp;
}

int XpShard::GetXp() const
{
	return _xp;
}

void XpShard::Destroy()
{
	_pickedUp = true;
}
