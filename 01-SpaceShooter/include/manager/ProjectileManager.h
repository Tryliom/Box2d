#pragma once
#include <SFML/Graphics.hpp>

#include "projectile/Projectile.h"

class ProjectileManager final : public sf::Drawable
{
private:
	ProjectileManager();

	std::list<Projectile*> _projectiles;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	ProjectileManager(const ProjectileManager&) = delete;
	ProjectileManager& operator=(const ProjectileManager&) = delete;

	static ProjectileManager& GetInstance()
	{
		static ProjectileManager instance;
		return instance;
	}

	void Update(sf::Time elapsed);

	void AddProjectile(Projectile* projectile);
};
