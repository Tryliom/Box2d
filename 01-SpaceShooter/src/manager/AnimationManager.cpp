#include "manager/AnimationManager.h"

AnimationManager::AnimationManager()
{
	_hitAnimations = {};
	_trails = {};
}

void AnimationManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& hitAnimation : _hitAnimations)
	{
		target.draw(hitAnimation, states);
	}

	for (const auto& trail : _trails)
	{
		target.draw(trail, states);
	}
}

void AnimationManager::AddHitAnimation(const sf::Vector2f position)
{
	_hitAnimations.emplace_back(position);
}

void AnimationManager::AddTrail(const sf::Vector2f position, const float angle, const Group group)
{
	_trails.emplace_back(position, angle, group);
}

void AnimationManager::Update(const sf::Time elapsed)
{
	for (auto it = _hitAnimations.begin(); it != _hitAnimations.end();)
	{
		it->Update(elapsed);

		if (it->IsFinished())
		{
			it = _hitAnimations.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (auto it = _trails.begin(); it != _trails.end();)
	{
		it->Update(elapsed);

		if (it->IsDead())
		{
			it = _trails.erase(it);
		}
		else
		{
			++it;
		}
	}
}