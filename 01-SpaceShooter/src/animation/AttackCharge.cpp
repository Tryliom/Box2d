#include "animation/AttackCharge.h"

CircleAnimation::CircleAnimation(const sf::Vector2f position, const float radius, const float duration)
{
	_shape.setRadius(radius);
	_shape.setOrigin(radius, radius);
	_shape.setPosition(position);
	_shape.setFillColor(sf::Color::Transparent);
	_shape.setOutlineColor(sf::Color(255, 255, 255, 20));
	_shape.setOutlineThickness(1.0f);

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

	_shape.setOutlineThickness(2.0f + 10.0f * percentage);
	_shape.setOutlineColor(sf::Color(255, 255, 255, 20 + 235 * percentage));
	_shape.setScale(1.0f - 1.f * percentage, 1.0f - 1.f * percentage);
}

void CircleAnimation::UpdatePosition(const sf::Vector2f position)
{
	_shape.setPosition(position);
}

AttackCharge::AttackCharge()
{
	_position = sf::Vector2f(0.0f, 0.0f);
	_radius = 0.0f;

	_duration = sf::seconds(0.f);
	_currentDuration = sf::Time::Zero;

	_timeBetweenAnimations = sf::seconds(0.f);
	_currentTimeBetweenAnimations = sf::Time::Zero;
}

AttackCharge::AttackCharge(const sf::Vector2f position, const float radius, const float duration)
{
	_position = position;
	_radius = radius;

	_duration = sf::seconds(duration);
	_currentDuration = sf::Time::Zero;

	addCircleAnimation();
}

void AttackCharge::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	for (const auto& animation : _animations)
	{
		target.draw(animation, states);
	}
}

void AttackCharge::addCircleAnimation()
{
	const float leftDuration = (_duration - _currentDuration).asSeconds();

	if (leftDuration > 0.0f)
	{
		_timeBetweenAnimations = sf::seconds(leftDuration / 10.0f);
		_currentTimeBetweenAnimations = sf::Time::Zero;

		_animations.emplace_back(_position, _radius, _timeBetweenAnimations.asSeconds());
	}
}

void AttackCharge::Update(const sf::Time elapsed)
{
	_currentDuration += elapsed;

	_currentTimeBetweenAnimations += elapsed;
	if (_currentTimeBetweenAnimations >= _timeBetweenAnimations)
	{
		addCircleAnimation();
	}

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

void AttackCharge::Stop()
{
	_currentDuration = _duration;
}

void AttackCharge::UpdatePosition(sf::Vector2f position)
{
	_position = position;

	for (auto& animation : _animations)
	{
		animation.UpdatePosition(position);
	}
}
