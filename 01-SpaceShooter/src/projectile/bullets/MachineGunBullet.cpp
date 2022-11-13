#include "projectile/bullets/MachineGunBullet.h"

#include "Assets.h"

MachineGunBullet::MachineGunBullet(b2Body* body, sf::Vector2f position, float angle, float size, b2Vec2 velocity,
	sf::Time lifeTime, float damage, Group groupIndex, bool trail) :
	Projectile(body, position, Assets::GetInstance().GetTexture(Texture::MACHINE_GUN_BULLET), ShapeType::CIRCLE, angle, size, velocity,
		lifeTime, damage, false, groupIndex, trail)
{}