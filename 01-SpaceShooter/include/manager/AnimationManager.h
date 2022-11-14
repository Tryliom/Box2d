#pragma once
#include <list>

#include "animation/DeathAnimation.h"
#include "animation/HitAnimation.h"
#include "animation/TextAnimation.h"
#include "animation/Trail.h"

class AnimationManager final
{
private:
	AnimationManager();

	std::list<HitAnimation> _hitAnimations;
	std::list<DeathAnimation> _deathAnimations;
	std::list<Trail> _trails;
	std::list<TextAnimation> _textAnimations;

public:
	AnimationManager(const AnimationManager&) = delete;
	AnimationManager& operator=(const AnimationManager&) = delete;

	static AnimationManager& GetInstance()
	{
		static AnimationManager instance;
		return instance;
	}

	void AddHitAnimation(const HitAnimation& hitAnimation);
	void AddTrail(const Trail& trail);
	void AddTextAnimation(const TextAnimation& textAnimation);
	void AddDeathAnimation(const DeathAnimation& deathAnimation);

	void DrawHitAnimations(sf::RenderWindow& window) const;
	void DrawTrails(sf::RenderWindow& window) const;
	void DrawTextAnimations(sf::RenderWindow& window) const;
	void DrawDeathAnimations(sf::RenderWindow& window) const;

	void Update(sf::Time elapsed);
};
