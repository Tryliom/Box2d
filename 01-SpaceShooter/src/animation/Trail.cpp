#include "animation/Trail.h"

#include "Assets.h"

Trail::Trail(const sf::Vector2f position, const float angle, const Group group)
{
	const sf::Texture& texture = Assets::GetInstance().GetTexture(Texture::SNIPER_TRAIL);

	_group = group;

	_sprite.setTexture(texture);
	_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	_sprite.setPosition(position);
	_sprite.setRotation(angle);
	_sprite.setColor(GetColor(group));

	_lifeTime = sf::seconds(0.5f);
	_currentLifeTime = sf::Time::Zero;
}

void Trail::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void Trail::Update(const sf::Time elapsed)
{
	_currentLifeTime += elapsed;

	sf::Uint8 alpha = 255 - static_cast<sf::Uint8>(_currentLifeTime.asSeconds() / _lifeTime.asSeconds() * 255);
	sf::Color color = _sprite.getColor();
	color.a = alpha;

	_sprite.setColor(color);
}