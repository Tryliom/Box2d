#include "Game.h"

#include "Assets.h"

Game::Game() :
	_window(sf::RenderWindow(sf::VideoMode(1920, 1080), "Space Shooter")),
	_world(b2World(b2Vec2(0.0f, -30.f)))
{

	// Set the background to the size of the window
	_background.setSize(sf::Vector2f(_window.getSize()));
	_background.setPosition(0.f, 0.f);

	_background.setTexture(&Assets::GetInstance().GetTexture(Texture::BACKGROUND));

	// Set the size of the game
	Game::HEIGHT = _window.getSize().y;
	Game::WIDTH = _window.getSize().x;
}

void Game::update(const sf::Time elapsed)
{
	_world.Step(elapsed.asSeconds(), 8, 3);
}

void Game::checkInputs(const sf::Event event)
{
	if (event.type == sf::Event::Closed)
		_window.close();
}

void Game::render()
{
	_window.clear();

	// Render background
	_window.draw(_background);

	_window.display();
}

b2Body* Game::getNewBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0f);
	return _world.CreateBody(&bodyDef);
}

sf::Vector2f Game::MeterToPixel(const b2Vec2 meter)
{
	return { XMeterToPixel(meter.x), YMeterToPixel(meter.y) };
}

b2Vec2 Game::PixelToMeter(const sf::Vector2f pixel)
{
	return { XPixelToMeter(pixel.x), YPixelToMeter(pixel.y) };
}

float Game::XMeterToPixel(const float xMeter)
{
	return xMeter * SCALE;
}

float Game::YMeterToPixel(const float yMeter)
{
	return HEIGHT - yMeter * SCALE;
}

float Game::MeterToPixel(const float meter)
{
	return meter * SCALE;
}

float Game::XPixelToMeter(const float xPixel)
{
	return xPixel / SCALE;
}

float Game::YPixelToMeter(const float yPixel)
{
	return (HEIGHT - yPixel) / SCALE;
}

float Game::PixelToMeter(const float pixel)
{
	return pixel / SCALE;
}

int Game::Loop()
{
	sf::Clock clock;

	while (_window.isOpen())
	{
		sf::Event event{};

		while (_window.pollEvent(event))
		{
			checkInputs(event);
		}

		update(clock.restart());
		render();
	}

	return EXIT_SUCCESS;
}
