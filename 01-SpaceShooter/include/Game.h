#pragma once
#include "player/Player.h"
#include "Assets.h"

#include "SFML/Graphics.hpp"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>

#include "box2d/b2_body.h"
#include "box2d/b2_world.h"

class Game final
{
public:
	Game();

private:
	sf::RenderWindow _window;
	b2World _world;
	sf::Music _music;
	sf::Sound _burstSound;
	std::vector<sf::Sound> _sounds;

	// Background
	sf::RectangleShape _background;

	// Entities
	Player _player;

	void update(sf::Time elapsed);
	void checkInputs(sf::Event event);
	void render();

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

	static float RadToDegree(float angle);
	static float DegreeToRad(float angle);

	int Loop();

	b2Body* GetNewBody();

	sf::RenderWindow& GetWindow() { return _window; }
	b2World& GetWorld() { return _world; }

	void PlaySound(Sound sound);
};