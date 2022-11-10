#pragma once
#include <SFML/Graphics.hpp>

constexpr int HIT_ANIMATION_FRAMES = 10;
constexpr float HIT_ANIMATION_DURATION = 1.f / 24.f;

class HitAnimation final : public sf::Drawable
{
public:
	HitAnimation(sf::Vector2f position);

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