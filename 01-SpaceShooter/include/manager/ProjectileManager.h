#pragma once
#include <SFML/Graphics.hpp>

#include "projectile/Projectile.h"

class ProjectileManager final : public sf::Drawable
{
public:
	ProjectileManager();

private:
	std::list<Projectile*> _projectiles;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Update(sf::Time elapsed);

	void AddProjectile(Projectile* projectile);
};
