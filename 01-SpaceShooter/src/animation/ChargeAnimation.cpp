#include "animation/ChargeAnimation.h"

ChargeAnimation::ChargeAnimation(sf::Vector2f position, float duration)
{
	_position = position;

	_duration = sf::seconds(duration);
	_currentDuration = sf::Time::Zero;

	_timeBetweenAnimations = sf::seconds(0.f);
	_currentTimeBetweenAnimations = sf::Time::Zero;
}

void ChargeAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const {}

void ChargeAnimation::addAnimation()
{
	_currentTimeBetweenAnimations = sf::Time::Zero;
}

void ChargeAnimation::Update(const sf::Time elapsed)
{
	_currentDuration += elapsed;

	_currentTimeBetweenAnimations += elapsed;
	if (_currentTimeBetweenAnimations >= _timeBetweenAnimations)
	{
		addAnimation();
	}
}

void ChargeAnimation::Stop()
{
	_currentDuration = _duration;
}

void ChargeAnimation::UpdatePosition(const sf::Vector2f position)
{
	_position = position;
}
