#pragma once
#include <SFML/Graphics.hpp>

#include "animation/ChargeAnimation.h"

// Each circle used in attack charge
class CircleAnimation final : public sf::Drawable
{
public:
	CircleAnimation(sf::Vector2f position, float radius, float duration);

protected:
	sf::CircleShape _shape;
	sf::Time _duration;
	sf::Time _currentDuration;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Update(sf::Time elapsed);
	void UpdatePosition(sf::Vector2f position);

	bool IsFinished() const { return _currentDuration >= _duration; }
};

class CircleAttackCharge final : public ChargeAnimation
{
public:
	CircleAttackCharge() = default;
	CircleAttackCharge(sf::Vector2f position, float radius, float duration);

protected:
	float _radius{0.f};

	std::vector<CircleAnimation> _animations;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void addAnimation() override;

public:
	void Update(sf::Time elapsed) override;
	void UpdatePosition(sf::Vector2f position) override;
};