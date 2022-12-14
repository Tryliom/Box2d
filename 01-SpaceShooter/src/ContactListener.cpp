#include "ContactListener.h"

#include "entity/Entity.h"
#include "box2d/b2_contact.h"
#include "Game.h"
#include "entity/Player.h"
#include "projectile/XpShard.h"

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


		if (!entityA->IsDead() && !entityB->IsDead() 
			&& !entityA->GetBody()->GetFixtureList()->IsSensor() && !entityB->GetBody()->GetFixtureList()->IsSensor())
		{
			entityA->TakeDamage(entityB);
			entityB->TakeDamage(entityA);
		}
	}
	else if ((groupA == Group::PLAYER && groupB == Group::ENEMY_PROJECTILE) || (groupA == Group::ENEMY_PROJECTILE && groupB == Group::PLAYER) ||
			 (groupA == Group::PLAYER_PROJECTILE && groupB == Group::ENEMY) || (groupA == Group::ENEMY && groupB == Group::PLAYER_PROJECTILE))
	{
		// Player hit an enemy projectile
		Entity* entity = nullptr;
		Projectile* projectile = nullptr;

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

		if (!projectile->IsDead() && !entity->IsDead())
		{
			// Get the point between the two bodies
			const sf::Vector2f bodyPosition = Game::MeterToPixel(entity->GetBody()->GetPosition());
			const sf::Vector2f projectilePosition = Game::MeterToPixel(projectile->GetBody()->GetPosition());
			const sf::Vector2f impactPosition = bodyPosition + (projectilePosition - bodyPosition) / 2.f;

			entity->TakeDamage(projectile);
			projectile->OnImpact(impactPosition);
		}
	}
	else if (groupA == Group::PLAYER && groupB == Group::XP || groupA == Group::XP && groupB == Group::PLAYER)
	{
		// Player hit XP
		Player* player = nullptr;
		XpShard* xpShard = nullptr;

		if (groupA == Group::PLAYER)
		{
			player = reinterpret_cast<Player*>(aPointer);
			xpShard = reinterpret_cast<XpShard*>(bPointer);
		}
		else
		{
			player = reinterpret_cast<Player*>(bPointer);
			xpShard = reinterpret_cast<XpShard*>(aPointer);
		}

		if (!xpShard->IsPickedUp() && !player->IsDead())
		{
			player->Contact(xpShard);
			xpShard->Destroy();
		}
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
