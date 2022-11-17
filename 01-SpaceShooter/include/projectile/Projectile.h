#pragma once
#include <list>

#include "DrawableObject.h"
#include "Group.h"
#include "animation/HitAnimation.h"

#include "box2d/b2_world.h"

enum class ShapeType
{
	RECTANGLE,
	CIRCLE
};

class Projectile : public DrawableObject
{
public:
	/**
	 * \brief Creates a new projectile
	 * \param body The body of the projectile
	 * \param position The position of the projectile
	 * \param texture The texture of the projectile
	 * \param shapeType The shape of the projectile
	 * \param angle The angle of the projectile in degrees
	 * \param size The size of the projectile
	 * \param velocity The velocity of the projectile
	 * \param lifeTime The lifetime of the projectile (in seconds)
	 * \param damage The damage of the projectile, if it can pierce, it will be divided by seconds
	 * \param canPierce Can the projectile pierce through multiple enemies?
	 * \param groupIndex The group index of the projectile
	 * \param trail If the projectile has a trail
	 */
	Projectile(
		b2Body* body, sf::Vector2f position, 
		const sf::Texture& texture, ShapeType shapeType,
		float angle, float size, b2Vec2 velocity, sf::Time lifeTime,
		float damage, bool canPierce, Group groupIndex, bool trail = false
	);

protected:
	sf::Sprite _sprite;

	sf::Time _lifeTime;
	sf::Time _currentLifeTime;

	float _size;
	float _damage;
	bool _canPierce;
	Group _groupIndex;
	bool _trail;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Update(sf::Time elapsed) override;
	void OnImpact(sf::Vector2f impactPoint);

	bool IsDead() const;

	float GetDamage() const { return _damage; }
};
