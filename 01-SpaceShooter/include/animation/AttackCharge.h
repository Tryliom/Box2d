#pragma once
#include <SFML/Graphics.hpp>

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

class AttackCharge final : public sf::Drawable
{
public:
	AttackCharge();
	AttackCharge(sf::Vector2f position, float radius, float duration);

protected:
	sf::Vector2f _position;
	float _radius;

	std::vector<CircleAnimation> _animations;
	sf::Time _duration;
	sf::Time _currentDuration;

	sf::Time _timeBetweenAnimations;
	sf::Time _currentTimeBetweenAnimations;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void addCircleAnimation();

public:
	void Update(sf::Time elapsed);
	void Stop();
	void UpdatePosition(sf::Vector2f position);

	bool IsFinished() const { return _currentDuration >= _duration; }
};