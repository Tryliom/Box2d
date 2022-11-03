#include "DrawableObject.h"

#include "Game.h"

DrawableObject::DrawableObject(b2Body* body, sf::Vector2f position)
{
	_body = body;

	_body->SetTransform(Game::PixelToMeter(position), 0.f);
}
