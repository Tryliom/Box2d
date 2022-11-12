#pragma once
#include <SFML/Graphics.hpp>

#include "Group.h"

class Trail final : public sf::Drawable
{
public:
	Trail(sf::Vector2f position, float angle, Group group);

private:
	Group _group;
	sf::Sprite _sprite;
	sf::Time _lifeTime;
	sf::Time _currentLifeTime;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Update(sf::Time elapsed);

	bool IsDead() const { return _currentLifeTime >= _lifeTime; }
};
