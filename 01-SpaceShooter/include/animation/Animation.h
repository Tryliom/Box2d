#pragma once
#include <SFML/Graphics.hpp>

#include "Assets.h"

enum class EndAnimationType
{
	FADE,
	FADE_IN_AND_OUT,
	SCALE_UP,
	SCALE_DOWN,
	ROTATE_LEFT,
	ROTATE_RIGHT
};

struct AnimationEffect
{
	EndAnimationType Type;
	float BaseValue{ 0.f };
	float EndValue{ 0.f };
};

class Animation : public sf::Drawable
{
public:
	Animation(sf::Vector2f position, Texture texture, sf::Time lifeTime, 
			  const std::vector<AnimationEffect>& endAnimationTypes, sf::Color color = sf::Color::White);

protected:
	sf::Sprite _sprite;

	sf::Time _lifeTime;
	sf::Time _currentLifeTime;

	std::vector<AnimationEffect> _endAnimationTypes;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Update(sf::Time elapsed);
	bool IsFinished() const;
};

class AttackAnimation final : public Animation
{
public:
	AttackAnimation(sf::Vector2f position) : Animation(position, Texture::CHARGE_CIRCLE, sf::seconds(0.1f),
		{
			{ EndAnimationType::FADE, 255.f, -255.f },
			{ EndAnimationType::SCALE_UP, 1.f, 0.5f },
			{ EndAnimationType::SCALE_DOWN, 1.f, 0.5f }
		})
	{}
};