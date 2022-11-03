#pragma once

#include "box2d/b2_body.h"
#include "box2d/b2_world.h"

#include "SFML/Graphics.hpp"

class Game final
{
public:
	Game();

private:
	sf::RenderWindow _window;
	b2World _world;

	// Background
	sf::RectangleShape _background;

	void update(sf::Time elapsed);
	void checkInputs(sf::Event event);
	void render();

	b2Body* getNewBody();

public:
	inline static float HEIGHT = 0.f;
	inline static float WIDTH = 0.f;
	inline static float SCALE = 10.0f;

	static sf::Vector2f MeterToPixel(b2Vec2 meter);
	static b2Vec2 PixelToMeter(sf::Vector2f pixel);

	static float XMeterToPixel(float xMeter);
	static float YMeterToPixel(float yMeter);
	static float MeterToPixel(float meter);

	static float XPixelToMeter(float xPixel);
	static float YPixelToMeter(float yPixel);
	static float PixelToMeter(float pixel);

	int Loop();
};