#include "animation/chargeAnimations/CircleAttackCharge.h"

CircleAnimation::CircleAnimation(const sf::Vector2f position, const float radius, const float duration)
{
	_shape.setRadius(radius);
	_shape.setOrigin(radius, radius);
	_shape.setPosition(position);
	_shape.setFillColor(sf::Color::Transparent);
	_shape.setOutlineColor(sf::Color(255, 255, 255, 20));
	_shape.setOutlineThickness(5.0f);

	_duration = sf::seconds(duration);
	_currentDuration = sf::Time::Zero;
}

void CircleAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape, states);
}

void CircleAnimation::Update(const sf::Time elapsed)
{
	_currentDuration += elapsed;

	const float percentage = _currentDuration.asSeconds() / _duration.asSeconds();
	
	_shape.setOutlineColor(sf::Color(255, 255, 255, 20 + 235 * percentage));
	_shape.setScale(1.0f - 1.f * percentage, 1.0f - 1.f * percentage);
}

void CircleAnimation::UpdatePosition(const sf::Vector2f position)
{
	_shape.setPosition(position);
}

CircleAttackCharge::CircleAttackCharge(const sf::Vector2f position, const float radius, const float duration) :
	ChargeAnimation(position, duration)
{
	_radius = radius;

	addAnimation();
}

void CircleAttackCharge::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	for (const auto& animation : _animations)
	{
		target.draw(animation, states);
	}
}

void CircleAttackCharge::addAnimation()
{
	const float leftDuration = (_duration - _currentDuration).asSeconds();

	if (leftDuration > 0.0f)
	{
		_timeBetweenAnimations = sf::seconds(_duration.asSeconds());
		_currentTimeBetweenAnimations = sf::Time::Zero;

		_animations.emplace_back(_position, _radius, _timeBetweenAnimations.asSeconds());
	}
}

void CircleAttackCharge::Update(const sf::Time elapsed)
{
	ChargeAnimation::Update(elapsed);

	for (auto& animation : _animations)
	{
		animation.Update(elapsed);
	}

	_animations.erase(std::remove_if(_animations.begin(), _animations.end(), [](const CircleAnimation& animation)
		{
			return animation.IsFinished();
		}
	), _animations.end());
}

void CircleAttackCharge::UpdatePosition(sf::Vector2f position)
{
	ChargeAnimation::UpdatePosition(position);

	for (auto& animation : _animations)
	{
		animation.UpdatePosition(position);
	}
}

void CircleAttackCharge::Stop()
{
	ChargeAnimation::Stop();

	_animations.clear();
}
