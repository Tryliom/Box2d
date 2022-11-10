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
