#include "projectile/bullets/Spark.h"

#include "Assets.h"
#include "Group.h"
#include "Game.h"

Spark::Spark(b2Body* body, const sf::Vector2f position, const float angle, float size, const b2Vec2 velocity, const float damage, Group group) :
	Projectile(body, position, Assets::GetInstance().GetTexture(Texture::SPARKS), ShapeType::RECTANGLE,
		angle, size, velocity, sf::seconds(0.5f),
		damage, true, group
	)
{}

void Spark::Update(const sf::Time elapsed)
{
	Projectile::Update(elapsed);

	// Make the sparks texture more transparent over time
	_sprite.setColor(sf::Color(255, 255, 255, 255 - (255 * _currentLifeTime.asSeconds() / _lifeTime.asSeconds())));

	// Scale the body
	_body->GetFixtureList()->GetShape()->m_radius = Game::PixelToMeter(_sprite.getGlobalBounds().width / 2.f);
}
