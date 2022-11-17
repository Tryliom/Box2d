#include "projectile/bullets/ShotGunBullet.h"

#include "Assets.h"

ShotGunBullet::ShotGunBullet(b2Body* body, sf::Vector2f position, float angle, float size, b2Vec2 velocity,
                             sf::Time lifeTime, float damage, Group groupIndex, bool trail) :
	Projectile(body, position, Assets::GetInstance().GetTexture(Texture::SHOT_GUN_BULLET), ShapeType::RECTANGLE, angle, size, velocity,
		lifeTime, damage, false, groupIndex, trail)
{}
