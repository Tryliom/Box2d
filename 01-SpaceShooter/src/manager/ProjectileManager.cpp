#include "manager/ProjectileManager.h"

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
}

void ProjectileManager::AddProjectile(Projectile* projectile)
{
	_projectiles.emplace_back(projectile);
}
