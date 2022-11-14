#include "animation/DeathAnimation.h"

#include <iostream>

#include "Assets.h"

DeathAnimation::DeathAnimation(const sf::Vector2f position)
{
	const sf::Texture& texture = Assets::GetInstance().GetDeathAnimationTexture(_currentFrame);

	_sprite.setTexture(texture);
	_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	_sprite.setPosition(position);

	_position = position;
}

void DeathAnimation::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void DeathAnimation::Update(const sf::Time elapsed)
{
	_currentDuration += elapsed;

	if (_currentDuration >= sf::seconds(ANIMATION_DURATION))
	{
		_currentDuration = sf::Time::Zero;
		_currentFrame++;

		if (_currentFrame >= Assets::GetInstance().GetDeathAnimationTextureCount())
		{
			return;
		}

		const sf::Texture& texture = Assets::GetInstance().GetDeathAnimationTexture(_currentFrame);

		_sprite.setTexture(texture);
		_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
		_sprite.setPosition(_position);
	}

	const float percent = (_currentFrame * ANIMATION_DURATION + _currentDuration.asSeconds()) / (Assets::GetInstance().GetDeathAnimationTextureCount() * ANIMATION_DURATION);
	const sf::Uint8 alpha = 255 - static_cast<sf::Uint8>(255.f * percent);

	_sprite.setColor(sf::Color(255, 255, 255, alpha));
}

bool DeathAnimation::IsFinished() const
{
	return _currentFrame >= Assets::GetInstance().GetDeathAnimationTextureCount();
}