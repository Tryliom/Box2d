#include "animation/chargeAnimations/CircleAttackCharge.h"

#include "Assets.h"

CircleAnimation::CircleAnimation(const sf::Vector2f position, const float radius, const float duration)
{
	const sf::Texture& texture = Assets::GetInstance().GetTexture(Texture::CHARGE_CIRCLE);

	_sprite.setTexture(texture);
	_sprite.setPosition(position);
	_sprite.setOrigin(sf::Vector2f(texture.getSize()) / 2.0f);
	_sprite.setScale(1.5f * radius / texture.getSize().x, 1.5f * radius / texture.getSize().y);
	_sprite.setColor(sf::Color(255, 255, 255, 0));

	_originalScale = _sprite.getScale();

	_duration = sf::seconds(duration);
	_currentDuration = sf::Time::Zero;
}

void CircleAnimation::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void CircleAnimation::Update(const sf::Time elapsed)
{
	_currentDuration += elapsed;

	const float percentage = _currentDuration.asSeconds() / _duration.asSeconds();
	
	_sprite.setColor(sf::Color(255, 255, 255, 255 * percentage));
	_sprite.setScale(_originalScale * (1.f - 1.f * percentage));
	_sprite.setRotation(_sprite.getRotation() + 360.f * elapsed.asSeconds());
}

void CircleAnimation::UpdatePosition(const sf::Vector2f position)
{
	_sprite.setPosition(position);
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
