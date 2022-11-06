#include "projectile/Trail.h"

#include "Assets.h"
#include "Game.h"
#include "Random.h"

Trail::Trail(b2Body* body, const sf::Vector2f position, const float angle, const float damage) :
	Projectile(
		body, position, Assets::GetInstance().GetTexture(Texture::TRAIL),
		angle, b2Vec2(0.f, 0.f), sf::seconds(Random::GetFloat(0.3f, 0.7f)),
		damage, true, Group::PLAYER_PROJECTILE
	)
{
	_sprite.setOrigin(_sprite.getTexture()->getSize().x / 2.f, 0.f);
}

void Trail::Update(const sf::Time elapsed)
{
	Projectile::Update(elapsed);

	// Make the trail texture more transparent over time
	_sprite.setColor(sf::Color(255, 255, 255, 255 - (255 * _currentLifeTime.asSeconds() / _lifeTime.asSeconds())));

	// Make the trail bigger over time
	_sprite.setScale(0.5f + 1.5f * _currentLifeTime.asSeconds() / _lifeTime.asSeconds(), 0.5f + 1.5f * _currentLifeTime.asSeconds() / _lifeTime.asSeconds());
}
