#include "projectile/bullets/PenetrationBullet.h"

#include "Assets.h"
#include "Group.h"
#include "Game.h"

PenetrationBullet::PenetrationBullet(b2Body* body, sf::Vector2f position, float angle, float size, b2Vec2 velocity,
	sf::Time lifeTime, float damage, Group groupIndex) :
	Projectile(body, position, Assets::GetInstance().GetTexture(Texture::SPARKS), ShapeType::RECTANGLE,
		angle, size, velocity, lifeTime,
		damage, true, groupIndex
	)
{}

void PenetrationBullet::Update(const sf::Time elapsed)
{
	Projectile::Update(elapsed);

	// Make the sparks texture more transparent over time
	_sprite.setColor(sf::Color(255, 255, 255, 255 - (255 * _currentLifeTime.asSeconds() / _lifeTime.asSeconds())));

	// Scale the body
	_body->GetFixtureList()->GetShape()->m_radius = Game::PixelToMeter(_sprite.getGlobalBounds().width / 2.f);
}
