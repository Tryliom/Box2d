#pragma once
#include "DrawableObject.h"
#include "Group.h"

class Projectile : public DrawableObject
{
public:
	/**
	 * \brief Creates a new projectile
	 * \param body The body of the projectile
	 * \param position The position of the projectile
	 * \param texture The texture of the projectile
	 * \param angle The angle of the projectile in degrees
	 * \param velocity The velocity of the projectile
	 * \param lifeTime The lifetime of the projectile (in seconds)
	 * \param damage The damage of the projectile, if it can pierce, it will be divided by seconds
	 * \param canPierce Can the projectile pierce through multiple enemies?
	 * \param groupIndex The group index of the projectile
	 */
	Projectile(b2Body* body, sf::Vector2f position, const sf::Texture& texture,
		float angle, b2Vec2 velocity, sf::Time lifeTime,
		float damage, bool canPierce, Group groupIndex
	);

protected:
	sf::Sprite _sprite;

	sf::Time _lifeTime;
	sf::Time _currentLifeTime;

	float _damage;
	bool _canPierce;
	Group _groupIndex;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Update(sf::Time elapsed) override;

	virtual void OnImpact();

	bool IsDead() const { return _currentLifeTime >= _lifeTime; }

	float GetDamage() const { return _damage; }
	bool CanPierce() const { return _canPierce; }
	Group GetGroupIndex() const { return _groupIndex; }
};
