#pragma once
#include "SFML/Graphics.hpp"

#include "box2d/b2_body.h"

// An object that is drawable and linked to box2d physic world
class DrawableObject : public sf::Drawable
{
public:
	DrawableObject(b2Body* body, sf::Vector2f position);

protected:
	b2Body* _body;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

public:
	[[nodiscard]] b2Body* GetBody() const { return _body; }

	virtual void Update(sf::Time elapsed) = 0;
};