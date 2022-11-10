#include "ContactListener.h"

#include "entity/Entity.h"
#include "box2d/b2_contact.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	// Get the two bodies that collided
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	const auto groupA = static_cast<Group>(bodyA->GetFixtureList()->GetFilterData().groupIndex);
	const auto groupB = static_cast<Group>(bodyB->GetFixtureList()->GetFilterData().groupIndex);

	const auto aPointer = contact->GetFixtureA()->GetUserData().pointer;
	const auto bPointer = contact->GetFixtureB()->GetUserData().pointer;

	if (groupA == Group::PLAYER && groupB == Group::ENEMY || groupA == Group::ENEMY && groupB == Group::PLAYER)
	{
		// Player hit an enemy
		auto* entityA = reinterpret_cast<Entity*>(aPointer);
		auto* entityB = reinterpret_cast<Entity*>(bPointer);

		entityA->TakeDamage(entityB);
		entityB->TakeDamage(entityA);
	}
	else if (groupA == Group::PLAYER && groupB == Group::ENEMY_PROJECTILE || groupA == Group::ENEMY_PROJECTILE && groupB == Group::PLAYER ||
		groupA == Group::PLAYER_PROJECTILE && groupB == Group::ENEMY || groupA == Group::ENEMY && groupB == Group::PLAYER_PROJECTILE)
	{
		// Player hit an enemy projectile
		Entity* entity;
		Projectile* projectile;

		if (groupA == Group::PLAYER || groupA == Group::ENEMY)
		{
			entity = reinterpret_cast<Entity*>(aPointer);
			projectile = reinterpret_cast<Projectile*>(bPointer);
		}
		else
		{
			entity = reinterpret_cast<Entity*>(bPointer);
			projectile = reinterpret_cast<Projectile*>(aPointer);
		}

		entity->TakeDamage(projectile);
		projectile->OnImpact();
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	
}
