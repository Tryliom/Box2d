#include "manager/ProjectileManager.h"

#include <iostream>

#include "manager/EntityManager.h"

ProjectileManager::ProjectileManager()
{
	_projectiles = {};
}

void ProjectileManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto* projectile : _projectiles)
	{
		target.draw(*projectile);
	}

	for (const auto* xpShard : _xpShards)
	{
		target.draw(*xpShard);
	}
}

void ProjectileManager::Update(const sf::Time elapsed)
{
	for (auto it = _projectiles.begin(); it != _projectiles.end();)
	{
		(*it)->Update(elapsed);

		if ((*it)->IsDead())
		{
			(*it)->GetBody()->GetWorld()->DestroyBody((*it)->GetBody());

			it = _projectiles.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (auto it = _xpShards.begin(); it != _xpShards.end();)
	{
		(*it)->Update(elapsed);

		// Apply force to xp shards to make them move to the player
		const b2Body* playerBody = EntityManager::GetInstance().GetPlayer()->GetBody();
		b2Vec2 direction = playerBody->GetPosition() - (*it)->GetBody()->GetPosition();
		direction.Normalize();
		direction *= 5.f;

		(*it)->GetBody()->SetLinearVelocity(direction);

		if ((*it)->IsPickedUp() || !EntityManager::GetInstance().IsPlayerAlive())
		{
			(*it)->GetBody()->GetWorld()->DestroyBody((*it)->GetBody());

			it = _xpShards.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void ProjectileManager::AddProjectile(Projectile* projectile)
{
	_projectiles.emplace_back(projectile);
}

void ProjectileManager::AddXpShard(XpShard* xpShard)
{
	_xpShards.emplace_back(xpShard);
}
