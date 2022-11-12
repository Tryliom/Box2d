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
	for (const auto projectile : _projectiles)
	{
		projectile->Update(elapsed);
	}

	// Remove projectiles that are dead
	erase_if(_projectiles, [](const auto* projectile) { return projectile->IsDead(); });
}

void ProjectileManager::AddProjectile(Projectile* projectile)
{
	_projectiles.emplace_back(projectile);
}
