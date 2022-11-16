#pragma once
#include <SFML/Graphics.hpp>

#include "Animation.h"

class TextAnimation : public sf::Drawable
{
public:
	TextAnimation(sf::Vector2f position, sf::Vector2f velocity, sf::Time duration, const std::vector<AnimationEffect>&
	              animationEffects,
		const std::string& text, unsigned int characterSize, sf::Color color = sf::Color::White);

private:
	sf::Text _text;
	sf::Vector2f _velocity;
	std::vector<AnimationEffect> _animationEffects;

	sf::Time _elapsedTime;
	sf::Time _duration;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Update(sf::Time elapsed);
	bool IsFinished() const;
};

class DamageTextAnimation final : public TextAnimation
{
public:
	DamageTextAnimation(sf::Vector2f position, const std::string& text, const sf::Color color = sf::Color::White) :
		TextAnimation(
			position,
			sf::Vector2f(0.f, 0.f),
			sf::seconds(0.75f),
			{
				{ EndAnimationType::FADE_IN_AND_OUT, 1.f, 1.f },
				{ EndAnimationType::SCALE_UP, 0.5f, 1.f },
			},
			text,
			20,
			color
		) {}
};

class WaveTextAnimation final : public TextAnimation
{
public:
	WaveTextAnimation(const sf::Vector2f position, const int waveNumber) :
		TextAnimation(
			position,
			sf::Vector2f(0.f, 0.f),
			sf::seconds(3.f),
			{
				{ EndAnimationType::FADE_IN_AND_OUT, 1.f, 1.f },
				{ EndAnimationType::SCALE_UP, 0.5f, 1.f },
			},
			"Wave " + std::to_string(waveNumber),
			50,
			sf::Color::White
			) {}
};