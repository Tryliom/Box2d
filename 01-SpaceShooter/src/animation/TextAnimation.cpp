#include "animation/TextAnimation.h"

#include <iostream>

TextAnimation::TextAnimation(sf::Vector2f position, sf::Vector2f velocity, sf::Time duration,
                             const std::vector<AnimationEffect>& animationEffects, const std::string& text, unsigned characterSize, sf::Color color)
{
	_text.setFont(Assets::GetInstance().GetFont(Font::PIXELMIX));
	_text.setString(text);
	_text.setCharacterSize(characterSize);
	_text.setFillColor(color);
	_text.setOrigin(_text.getLocalBounds().width / 2.f, _text.getLocalBounds().height / 2.f);
	_text.setPosition(position);
	_text.setFillColor(color);

	_velocity = velocity;
	_animationEffects = animationEffects;

	_elapsedTime = sf::Time::Zero;
	_duration = duration;
}

void TextAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_text, states);
}

void TextAnimation::Update(const sf::Time elapsed)
{
	_elapsedTime += elapsed;

	if (_elapsedTime >= _duration)
	{
		return;
	}

	const float percent = _elapsedTime.asSeconds() / _duration.asSeconds();

	for (const AnimationEffect& animationEffect : _animationEffects)
	{
		if (animationEffect.Type == EndAnimationType::FADE)
		{
			float alpha = 255.f * (animationEffect.BaseValue - animationEffect.EndValue * percent);

			if (alpha < 0.f)
			{
				alpha = 0.f;
			}
			else if (alpha > 255.f)
			{
				alpha = 255.f;
			}

			sf::Color color = _text.getFillColor();
			color.a = static_cast<sf::Uint8>(alpha);

			_text.setFillColor(color);
		}
		else if (animationEffect.Type == EndAnimationType::FADE_IN_AND_OUT)
		{
			float alpha = 0.f;

			// Fade in for the first half of the animation
			if (percent < 0.5f)
			{
				alpha = 255.f - 255.f * (animationEffect.BaseValue - animationEffect.EndValue * percent * 2.f);
			}
			// Fade out for the second half of the animation
			else
			{
				alpha = 255.f - 255.f * (animationEffect.BaseValue - animationEffect.EndValue * (1.f - percent) * 2.f);
			}

			if (alpha < 0.f)
			{
				alpha = 0.f;
			}
			else if (alpha > 255.f)
			{
				alpha = 255.f;
			}

			sf::Color color = _text.getFillColor();
			color.a = static_cast<sf::Uint8>(alpha);

			_text.setFillColor(color);
		}
		else if (animationEffect.Type == EndAnimationType::SCALE_UP)
		{
			const float scale = animationEffect.BaseValue + animationEffect.EndValue * percent;
			_text.setScale(scale, scale);
		}
		else if (animationEffect.Type == EndAnimationType::SCALE_DOWN)
		{
			const float scale = animationEffect.BaseValue - animationEffect.EndValue * percent;
			_text.setScale(scale, scale);
		}
		else if (animationEffect.Type == EndAnimationType::ROTATE_LEFT)
		{
			_text.setRotation(animationEffect.BaseValue + animationEffect.EndValue * percent);
		}
		else if (animationEffect.Type == EndAnimationType::ROTATE_RIGHT)
		{
			_text.setRotation(animationEffect.BaseValue - animationEffect.EndValue * percent);
		}
	}

	_text.move(_velocity * elapsed.asSeconds());
}

bool TextAnimation::IsFinished() const
{
	return _elapsedTime >= _duration;
}