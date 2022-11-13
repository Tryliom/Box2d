#include "projectile/bullets/CanonBullet.h"

#include "Assets.h"
#include "Game.h"

CanonBullet::CanonBullet(b2Body* body, sf::Vector2f position, float angle, float size, b2Vec2 velocity,
                         sf::Time lifeTime, float damage, Group groupIndex, bool trail) :
	Projectile(body, position, Assets::GetInstance().GetTexture(Texture::CANON_BULLET), ShapeType::CIRCLE, angle, size, velocity, 
		lifeTime, damage, false, groupIndex, trail)
{}

void CanonBullet::Update(const sf::Time elapsed)
{
	Projectile::Update(elapsed);

	// Make the bullet rotate on himself over time
	_body->SetTransform(_body->GetPosition(), _body->GetAngle() + 8.f * elapsed.asSeconds());
}