#include "manager/AnimationManager.h"

AnimationManager::AnimationManager()
{
	_hitAnimations = {};
	_trails = {};
}

void AnimationManager::AddHitAnimation(const HitAnimation& hitAnimation)
{
	_hitAnimations.emplace_back(hitAnimation);
}

void AnimationManager::AddTrail(const Trail& trail)
{
	_trails.emplace_back(trail);
}

void AnimationManager::AddTextAnimation(const TextAnimation& textAnimation)
{
	_textAnimations.emplace_back(textAnimation);
}

void AnimationManager::AddDeathAnimation(const DeathAnimation& deathAnimation)
{
	_deathAnimations.emplace_back(deathAnimation);
}

void AnimationManager::DrawHitAnimations(sf::RenderWindow& window) const
{
	for (const auto& hitAnimation : _hitAnimations)
	{
		window.draw(hitAnimation);
	}
}

void AnimationManager::DrawTrails(sf::RenderWindow& window) const
{
	for (const auto& trail : _trails)
	{
		window.draw(trail);
	}
}

void AnimationManager::DrawTextAnimations(sf::RenderWindow& window) const
{
	for (const auto& textAnimation : _textAnimations)
	{
		window.draw(textAnimation);
	}
}

void AnimationManager::DrawDeathAnimations(sf::RenderWindow& window) const
{
	for (const auto& deathAnimation : _deathAnimations)
	{
		window.draw(deathAnimation);
	}
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

	for (auto it = _textAnimations.begin(); it != _textAnimations.end();)
	{
		it->Update(elapsed);

		if (it->IsFinished())
		{
			it = _textAnimations.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (auto it = _deathAnimations.begin(); it != _deathAnimations.end();)
	{
		it->Update(elapsed);

		if (it->IsFinished())
		{
			it = _deathAnimations.erase(it);
		}
		else
		{
			++it;
		}
	}
}
