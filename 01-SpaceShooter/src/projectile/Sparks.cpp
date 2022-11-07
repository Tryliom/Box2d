#include "projectile/Sparks.h"

#include "Assets.h"
#include "Group.h"

Sparks::Sparks(b2Body* body, const sf::Vector2f position, const float angle, const b2Vec2 velocity,
               const float damagePerSeconds) :
	Projectile(body, position, Assets::GetInstance().GetTexture(Texture::SPARKS),
		angle, velocity, sf::seconds(0.5f),
		damagePerSeconds, true, Group::PLAYER_PROJECTILE
	)
{}

void Sparks::Update(const sf::Time elapsed)
{
	Projectile::Update(elapsed);

	// Make the sparks texture more transparent over time
	_sprite.setColor(sf::Color(255, 255, 255, 255 - (255 * _currentLifeTime.asSeconds() / _lifeTime.asSeconds())));

	// Make the sparks smaller over time
	_sprite.setScale(2.f - 1.5f * _currentLifeTime.asSeconds() / _lifeTime.asSeconds(), 2.f - 1.5f * _currentLifeTime.asSeconds() / _lifeTime.asSeconds());
	// Scale the body
	_body->GetFixtureList()->GetShape()->m_radius = 2.f - 1.5f * _currentLifeTime.asSeconds() / _lifeTime.asSeconds();
}
