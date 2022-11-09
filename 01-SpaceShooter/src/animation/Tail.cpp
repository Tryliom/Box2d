#include "animation/Tail.h"

#include "Assets.h"
#include "Game.h"

Tail::Tail(const sf::Vector2f position, const float angle)
{
	const sf::Texture& texture = Assets::GetInstance().GetTexture(Texture::TAIL);

	_sprite.setTexture(texture);
	_sprite.setOrigin(texture.getSize().x / 2.f, 0.f);
	_sprite.setPosition(position);
	_sprite.setRotation(angle);

	_lifeTime = sf::seconds(0.3f);
	_currentLifeTime = sf::Time::Zero;
}

void Tail::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void Tail::Update(const sf::Time elapsed)
{
	_currentLifeTime += elapsed;

	// Make the tail texture more transparent over time
	_sprite.setColor(sf::Color(255, 255, 255, 255 - (255 * _currentLifeTime.asSeconds() / _lifeTime.asSeconds())));

	// Make the tail bigger over time
	_sprite.setScale(0.5f + 1.5f * _currentLifeTime.asSeconds() / _lifeTime.asSeconds(), 0.5f + 1.5f * _currentLifeTime.asSeconds() / _lifeTime.asSeconds());
}
