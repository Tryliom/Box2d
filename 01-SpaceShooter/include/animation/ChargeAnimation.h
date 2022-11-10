#pragma once
#include <SFML/Graphics.hpp>

class ChargeAnimation : public sf::Drawable
{
public:
	ChargeAnimation(sf::Vector2f position, float duration);

protected:
	sf::Vector2f _position;

	sf::Time _duration;
	sf::Time _currentDuration;

	sf::Time _timeBetweenAnimations;
	sf::Time _currentTimeBetweenAnimations;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	// Called each time between animations
	virtual void addAnimation();

public:
	virtual void Update(sf::Time elapsed);
	virtual void Stop();
	virtual void UpdatePosition(sf::Vector2f position);

	bool IsFullyCharged() const { return _currentDuration >= _duration; }
};
