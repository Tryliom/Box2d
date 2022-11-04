#include "Game.h"

#include "Assets.h"

Game::Game() :
	_window(sf::RenderWindow(sf::VideoMode(1920, 1080), "Space Shooter", sf::Style::Close)),
	_world(b2World(b2Vec2(0.0f, 0.f))),
	_player(*this, sf::Vector2f(100.f, 100.f))
{
	_window.setFramerateLimit(144);
	_window.setVerticalSyncEnabled(true);

	// Set the size of the game
	Game::HEIGHT = _window.getSize().y;
	Game::WIDTH = _window.getSize().x;

	// Set the background to the size of the window
	_background.setSize(sf::Vector2f(_window.getSize()));
	_background.setPosition(0.f, 0.f);

	_background.setTexture(&Assets::GetInstance().GetTexture(Texture::BACKGROUND));
}

void Game::update(const sf::Time elapsed)
{
	_world.Step(elapsed.asSeconds(), 8, 3);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		_player.Move();
	}

	_player.Update(elapsed);

	// If the player go out of the screen, teleport him to the other side
	if (_player.GetPosition().x < 0)
	{
		_player.SetPosition(sf::Vector2f(Game::WIDTH, _player.GetPosition().y));
	}
	else if (_player.GetPosition().x > Game::WIDTH)
	{
		_player.SetPosition(sf::Vector2f(0, _player.GetPosition().y));
	}
	else if (_player.GetPosition().y < 0)
	{
		_player.SetPosition(sf::Vector2f(_player.GetPosition().x, Game::HEIGHT));
	}
	else if (_player.GetPosition().y > Game::HEIGHT)
	{
		_player.SetPosition(sf::Vector2f(_player.GetPosition().x, 0));
	}
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

	// Render entities
	_window.draw(_player);

	_window.display();
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

float Game::RadToDegree(const float angle)
{
	return angle * 180.f / b2_pi;
}

float Game::DegreeToRad(const float angle)
{
	return angle * b2_pi / 180.f;
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

b2Body* Game::GetNewBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0f);

	return _world.CreateBody(&bodyDef);
}

void Game::PlaySound(const Sound sound)
{
	_sound.setBuffer(Assets::GetInstance().GetSound(sound));
	_sound.play();
}
