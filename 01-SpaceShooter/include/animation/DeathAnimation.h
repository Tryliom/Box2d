#pragma once
#include <SFML/Graphics.hpp>

class DeathAnimation final : public sf::Drawable
{
public:
	explicit DeathAnimation(sf::Vector2f position);

private:
	sf::Sprite _sprite;
	int _currentFrame{ 0 };
	sf::Vector2f _position;

	sf::Time _currentDuration;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Update(sf::Time elapsed);
	bool IsFinished() const;
};