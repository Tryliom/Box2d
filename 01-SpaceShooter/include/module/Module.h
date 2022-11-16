#pragma once
#include <SFML/System/Time.hpp>

#include "projectile/Projectile.h"

class Entity;

class Module
{
public:
	Module() = default;

protected:
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