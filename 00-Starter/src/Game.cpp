#include "Game.h"

#include "FixedRectangle.h"

Game::Game() :
	_window(sf::RenderWindow(sf::VideoMode(800, 600), "SFML & Box2d tests")),
	_world(b2World(b2Vec2(0.0f, -30.f)))
{
	_balls = {};
	_fixedObjects = {};
	HEIGHT = static_cast<float>(_window.getSize().y);
	WIDTH = static_cast<float>(_window.getSize().x);

	// Create the ground and the walls
	_fixedObjects.emplace_back(FixedRectangle(
		getNewBody(), 
		sf::Vector2f(WIDTH / 2.f, HEIGHT / 3.f),
		sf::Vector2f(WIDTH / 3.f, 30.0f),
		sf::Color::Red, 45.f, -180.f)
	);
	_fixedObjects.emplace_back(FixedRectangle(
		getNewBody(),
		sf::Vector2f(WIDTH / 2.f, HEIGHT * 2.f / 3.f),
		sf::Vector2f(WIDTH / 3.f, 30.0f),
		sf::Color::Red, -45.f, 180.f)
	);
	_fixedObjects.emplace_back(FixedRectangle(
		getNewBody(),
		sf::Vector2f(15.0f, HEIGHT / 2.f),
		sf::Vector2f(30.0f, HEIGHT),
		sf::Color::Red, 0.f)
	);
	_fixedObjects.emplace_back(FixedRectangle(
		getNewBody(),
		sf::Vector2f(WIDTH - 15.0f, HEIGHT / 2.f),
		sf::Vector2f(30.0f, HEIGHT),
		sf::Color::Red, 0.f)
	);
}

void Game::update(const sf::Time elapsed)
{
	_world.Step(elapsed.asSeconds(), 8, 3);

	for (auto& circle : _balls)
	{
		circle.Update(elapsed);

		auto totalForce = b2Vec2(0.f, 0.f);

		for (auto& blackHole : _blackHoles)
		{
			const auto distance = blackHole.GetBody()->GetPosition() - circle.GetBody()->GetPosition();
			auto forceVector = distance;

			forceVector.Normalize();
			forceVector *= 100000.f / distance.LengthSquared();

			totalForce += forceVector;
		}

		if (totalForce.Length() > 0.f)
		{
			circle.GetBody()->ApplyForceToCenter(totalForce, true);
		}
	}

	for (auto& rectangle : _fixedObjects)
	{
		rectangle.Update(elapsed);
	}

	for (auto& blackHole : _blackHoles)
	{
		blackHole.Update(elapsed);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		const auto mousePos = sf::Mouse::getPosition(_window);
		const auto body = getNewBody();

		_balls.emplace_back(BasicBall(body, sf::Vector2f(mousePos.x, mousePos.y)));
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	{
		// Make a shock wave by applying a force to all bodies
		for (auto& circle : _balls)
		{
			const auto mousePos = sf::Mouse::getPosition(_window);
			const auto mousePosInWorld = Game::PixelToMeter(sf::Vector2f(mousePos.x, mousePos.y));
			const auto body = circle.GetBody();
			const auto bodyPos = body->GetPosition();
			auto force = mousePosInWorld - bodyPos;

			force.Normalize();
			force *= -3000.f;

			body->ApplyForceToCenter(force, true);
		}
	}

	// Remove balls that are out of the window
	_balls.erase(std::remove_if(_balls.begin(), _balls.end(), [](const DrawableObject& ball) {
		return ball.GetBody()->GetPosition().y > HEIGHT;
		}
	), _balls.end());
}

void Game::checkInputs(const sf::Event event)
{
	if (event.type == sf::Event::Closed)
		_window.close();

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
	{
		const auto body = getNewBody();

		_blackHoles.emplace_back(BlackHole(body, sf::Vector2f(event.mouseButton.x, event.mouseButton.y)));
	}
}

void Game::render()
{
	_window.clear();

	for (auto& object : _fixedObjects)
	{
		_window.draw(object);
	}

	for (auto& circle : _balls)
	{
		_window.draw(circle);
	}

	for (auto& blackHole : _blackHoles)
	{
		_window.draw(blackHole);
	}

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
