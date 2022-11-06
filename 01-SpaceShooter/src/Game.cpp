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

	const sf::Texture& backgroundTexture = Assets::GetInstance().GetTexture(Texture::BACKGROUND);
	
	_background.setTexture(&backgroundTexture);
	_background.setSize(sf::Vector2f(backgroundTexture.getSize()));
	_background.setPosition(0.f, 0.f);
	_backgroundStep = 0.f;

	_player.SetPosition(sf::Vector2f(-100.f, HEIGHT + 100.f));
}

void Game::update(const sf::Time elapsed)
{
	_world.Step(elapsed.asSeconds(), 8, 3);

	_backgroundStep += elapsed.asSeconds() / 300.f;
	const float y = (HEIGHT - _background.getSize().y) / 2.f + std::cos(_backgroundStep * b2_pi) * (HEIGHT - _background.getSize().y) / 2.f;

	_background.setPosition(0.f, y);

	if (_stopBurstSound && _burstSound.getStatus() != sf::SoundSource::Stopped)
	{
		const float volume = _burstSound.getVolume() - 200.f * elapsed.asSeconds();

		if (volume <= 0.f)
		{
			_burstSound.stop();
			_stopBurstSound = false;
			_burstSound.setVolume(100.f);
		}
		else
		{
			_burstSound.setVolume(volume);
		}
	}

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

	// Remove the sounds that are finished
	_sounds.erase(std::remove_if(_sounds.begin(), _sounds.end(), [](sf::Sound& sound)
	{
		return sound.getStatus() == sf::Sound::Status::Stopped;
	}), _sounds.end());
}

void Game::checkInputs(const sf::Event event)
{
	if (event.type == sf::Event::Closed)
		_window.close();

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		_burstSound.setBuffer(Assets::GetInstance().GetSound(Sound::BURST));
		_burstSound.setLoop(true);
		_burstSound.play();
		_stopBurstSound = false;
		_burstSound.setVolume(100.f);
	}

	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		_burstSound.setLoop(false);
		_stopBurstSound = true;
	}

	// Player can charge a special attack (if he has any), for test purpose actually
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
	{
		_player.StartAttackAnimation();
	}

	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
	{
		_player.StopAttackAnimation();
	}
}

void Game::render()
{
	_window.clear();

	// Render background
	_window.draw(_background);

	// Render entities
	_window.draw(_player);

	renderHealthBar();

	_window.display();
}

void Game::renderHealthBar()
{
	// Draw health bar
	sf::RectangleShape healthBackgroundBar;
	healthBackgroundBar.setSize(sf::Vector2f(400.f, 8.f));
	healthBackgroundBar.setFillColor(sf::Color(40, 40, 40));
	healthBackgroundBar.setOrigin(healthBackgroundBar.getSize() / 2.f);
	healthBackgroundBar.setPosition({ Game::WIDTH / 2.f, Game::HEIGHT - 20.f });

	_window.draw(healthBackgroundBar);

	float healthPercentage = _player.GetHealthPercentage();

	if (healthPercentage < 0.f)
	{
		healthPercentage = 0.f;
	}

	sf::RectangleShape healthBar;
	healthBar.setSize(sf::Vector2f(healthBackgroundBar.getSize().x * healthPercentage, healthBackgroundBar.getSize().y));
	healthBar.setFillColor(sf::Color::Red);
	healthBackgroundBar.setOutlineColor(sf::Color::Black);
	healthBackgroundBar.setOutlineThickness(-0.5f);
	healthBar.setOrigin(healthBar.getSize() / 2.f);
	healthBar.setPosition(healthBackgroundBar.getPosition());

	_window.draw(healthBar);
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

b2Vec2 Game::GetLinearVelocity(const float speed, const float angleDegree)
{
	const float angle = Game::DegreeToRad(angleDegree - 90.f);
	const float x = speed * std::cos(angle);
	const float y = speed * std::sin(angle);

	return {x, -y};
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
	_sounds.emplace_back();
	_sounds.back().setBuffer(Assets::GetInstance().GetSound(sound));
	_sounds.back().play();
}
