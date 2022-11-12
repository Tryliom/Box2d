#pragma once
#include <list>
#include <SFML/Graphics/Drawable.hpp>

#include "animation/HitAnimation.h"
#include "animation/Trail.h"

class AnimationManager final : public sf::Drawable
{
public:
	AnimationManager();

private:
	std::list<HitAnimation> _hitAnimations;
	std::list<Trail> _trails;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void AddHitAnimation(sf::Vector2f position);
	void AddTrail(sf::Vector2f position, float angle, Group group);

	void Update(sf::Time elapsed);
};
