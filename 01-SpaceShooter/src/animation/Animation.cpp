#include "animation/Animation.h"

Animation::Animation(const sf::Vector2f position, const Texture texture, const sf::Time lifeTime, 
					 const std::vector<AnimationEffect>& endAnimationTypes, const sf::Color color)
{
	const sf::Texture& image = Assets::GetInstance().GetTexture(texture);

	_sprite.setTexture(image);
	_sprite.setOrigin(image.getSize().x / 2.f, image.getSize().y / 2.f);
	_sprite.setPosition(position);
	_sprite.setColor(color);

	_lifeTime = lifeTime;
	_currentLifeTime = sf::Time::Zero;

	_endAnimationTypes = endAnimationTypes;
}

void Animation::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void Animation::Update(const sf::Time elapsed)
{
	_currentLifeTime += elapsed;

	if (_currentLifeTime >= _lifeTime)
	{
		return;
	}

	const float percent = _currentLifeTime.asSeconds() / _lifeTime.asSeconds();

	for (const AnimationEffect& animationEffect : _endAnimationTypes)
	{
		if (animationEffect.Type == EndAnimationType::FADE)
		{
			const float alpha = 255.f * (animationEffect.BaseValue - animationEffect.EndValue * percent);
			_sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
		}
		else if (animationEffect.Type == EndAnimationType::SCALE_UP)
		{
			const float scale = animationEffect.BaseValue + animationEffect.EndValue * percent;
			_sprite.setScale(scale, scale);
		}
		else if (animationEffect.Type == EndAnimationType::SCALE_DOWN)
		{
			const float scale = animationEffect.BaseValue - animationEffect.EndValue * percent;
			_sprite.setScale(scale, scale);
		}
		else if (animationEffect.Type == EndAnimationType::ROTATE_LEFT)
		{
			_sprite.setRotation(animationEffect.BaseValue + animationEffect.EndValue * percent);
		}
		else if (animationEffect.Type == EndAnimationType::ROTATE_RIGHT)
		{
			_sprite.setRotation(animationEffect.BaseValue - animationEffect.EndValue * percent);
		}
	}
}

bool Animation::IsFinished() const
{
	return _currentLifeTime >= _lifeTime;
}
