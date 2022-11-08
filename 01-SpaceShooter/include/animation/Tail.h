#pragma once
#include <SFML/Graphics.hpp>

// This is the trail that the player leaves behind, stuck to the back of the ship
class Tail final : public sf::Drawable
{
public:
	Tail(sf::Vector2f position, float angle);

private:
	sf::Sprite _sprite;

	sf::Time _lifeTime;
	sf::Time _currentLifeTime;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Update(sf::Time elapsed);

	void SetAngle(const float angle) { _sprite.setRotation(angle); }
	void SetPosition(const sf::Vector2f position) { _sprite.setPosition(position); }

	bool IsDead() const { return _currentLifeTime >= _lifeTime; }
};