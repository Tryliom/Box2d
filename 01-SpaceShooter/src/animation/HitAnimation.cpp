#include "animation/HitAnimation.h"

#include "Assets.h"

HitAnimation::HitAnimation(const sf::Vector2f position)
{
	const sf::Texture& texture = Assets::GetInstance().GetHitAnimationTexture(_currentFrame);

	_sprite.setTexture(texture);
	_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	_sprite.setPosition(position);

	_position = position;
}

void HitAnimation::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void HitAnimation::Update(const sf::Time elapsed)
{
	_currentDuration += elapsed;

	if (_currentDuration >= sf::seconds(HIT_ANIMATION_DURATION))
	{
		_currentDuration = sf::Time::Zero;
		_currentFrame++;

		if (_currentFrame >= HIT_ANIMATION_FRAMES)
		{
			return;
		}

		const sf::Texture& texture = Assets::GetInstance().GetHitAnimationTexture(_currentFrame);

		_sprite.setTexture(texture);
		_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
		_sprite.setPosition(_position);
	}

	_sprite.setRotation(_sprite.getRotation() + 360.f * elapsed.asSeconds());
}

bool HitAnimation::IsFinished() const
{
	return _currentFrame >= HIT_ANIMATION_FRAMES;
}
