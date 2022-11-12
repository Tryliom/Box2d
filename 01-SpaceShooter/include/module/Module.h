#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

#include "projectile/Projectile.h"

class Entity;

class Module : public sf::Drawable
{
public:
	Module() = default;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

	virtual void updateData(Entity* entity) = 0;

public:
	virtual void Initialize(Entity* entity) = 0;

	// Events
	virtual void Update(sf::Time elapsed, Entity* entity) = 0;

	virtual void OnEntityDeath(Entity* entity) {}
	virtual void OnEntityHit(Entity* entity, Projectile* projectile) {}
	virtual void OnEntityHit(Entity* entity, Entity* projectile) {}
	virtual void OnEntityCollision(Entity* entity) {}
	virtual void OnEntityMove(Entity* entity) {}
};