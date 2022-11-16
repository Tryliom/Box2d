#include "Game.h"

#include "Assets.h"
#include "Random.h"
#include "entity/enemies/Camper.h"
#include "entity/enemies/Imperator.h"
#include "manager/AnimationManager.h"
#include "manager/AudioManager.h"
#include "manager/ProjectileManager.h"
#include "entity/enemies/Angel.h"
#include "gui/guis/GameOverGui.h"
#include "gui/guis/MenuGui.h"
#include "gui/guis/PauseGui.h"
#include "gui/guis/WeaponChoiceGui.h"
#include "manager/EntityManager.h"
#include "manager/HUDManager.h"

Game::Game() :
	_window(sf::RenderWindow(sf::VideoMode(1920, 1080), "Space Shooter", sf::Style::Fullscreen)),
	_world(b2World(b2Vec2(0.0f, 0.f)))
{
	_window.setFramerateLimit(144);
	_window.setVerticalSyncEnabled(true);

	// Set the size of the game
	HEIGHT = static_cast<float>(_window.getSize().y);
	WIDTH = static_cast<float>(_window.getSize().x);

	const std::vector backgrounds = { Texture::BACKGROUND, Texture::BACKGROUND2, Texture::BACKGROUND3 };
	const sf::Texture& backgroundTexture = Assets::GetInstance().GetTexture(backgrounds[Random::GetInt(0, backgrounds.size() - 1)]);
	
	_background.setTexture(&backgroundTexture);
	_background.setSize(sf::Vector2f(backgroundTexture.getSize()));
	_backgroundStep = 0.f;
	const float y = (HEIGHT - _background.getSize().y) / 2.f + std::cos(_backgroundStep * b2_pi) * (HEIGHT - _background.getSize().y) / 2.f;

	_background.setPosition(0.f, y);

	_world.SetContactListener(&_contactListener);

	AudioManager::GetInstance();
	SetState(GameState::MAIN_MENU);
}

void Game::update(const sf::Time elapsed)
{
	if (_state != GameState::PAUSE && _state != GameState::UPGRADE_CHOICE)
	{
		_world.Step(elapsed.asSeconds(), 8, 3);
		
		EntityManager::GetInstance().Update(elapsed, _state);
		ProjectileManager::GetInstance().Update(elapsed);
		AnimationManager::GetInstance().Update(elapsed);
		AudioManager::GetInstance().Update(elapsed);
		HUDManager::GetInstance().Update(elapsed);
	}

	if (_gui != nullptr)
	{
		_gui->Update(*this, elapsed);
	}
	else if (_state == GameState::PLAYING)
	{
		_backgroundStep += elapsed.asSeconds() / 100.f;
		const float y = (HEIGHT - _background.getSize().y) / 2.f + std::cos(_backgroundStep * b2_pi) * (HEIGHT - _background.getSize().y) / 2.f;

		_background.setPosition(0.f, y);

		_waveTime += elapsed;

		if (!EntityManager::GetInstance().AreEnemiesAlive() || _waveTime >= _waveDuration && _wave % 5 != 0)
		{
			spawnEnemies();
		}
	}
}

void Game::checkInputs(const sf::Event event)
{
	if (event.type == sf::Event::Closed)
	{
		_window.close();
		return;
	}

	if (_state == GameState::PLAYING)
	{
		EntityManager::GetInstance().CheckInputs(event);
		AudioManager::GetInstance().CheckInputs(event);
	}

	if (_state == GameState::PLAYING && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		SetState(GameState::PAUSE);
	}
	else if (_gui != nullptr)
	{
		_gui->CheckInputs(event, *this);
	}
}

void Game::render()
{
	const AnimationManager& animationManager = AnimationManager::GetInstance();

	_window.clear();

	// Render background
	_window.draw(_background);

	animationManager.DrawDeathAnimations(_window);
	animationManager.DrawTrails(_window);

	_window.draw(ProjectileManager::GetInstance());

	// Render entities
	_window.draw(EntityManager::GetInstance());

	animationManager.DrawHitAnimations(_window);
	animationManager.DrawTextAnimations(_window);

	if (_state != GameState::MAIN_MENU && _state != GameState::WEAPON_CHOICE)
	{
		_window.draw(HUDManager::GetInstance());
	}

	if (_gui != nullptr)
	{
		_window.draw(*_gui);
	}

	_window.display();
}

void Game::spawnEnemies()
{
	_wave++;
	_waveTime = sf::Time::Zero;
	_waveDuration += sf::seconds(2.f);

	EntityManager::GetInstance().RunAway();

	// Spawn enemies outside the screen
	const int number = Random::GetInt(_wave, 10 + _wave);

	if (_wave % 5 == 0)
	{
		EntityManager::GetInstance().SpawnEnemy(new Imperator(*this, sf::Vector2f(WIDTH / 2.f, -200.f)));
		EntityManager::GetInstance().SpawnEnemy(new Angel(*this, sf::Vector2f(WIDTH / 4.f, -200.f)));
		EntityManager::GetInstance().SpawnEnemy(new Angel(*this, sf::Vector2f(WIDTH * 3.f / 4.f, -200.f)));

		if (_wave >= 20)
		{
			EntityManager::GetInstance().SpawnEnemy(new Imperator(*this, sf::Vector2f(WIDTH / 2.f, HEIGHT + 200.f)));
			EntityManager::GetInstance().SpawnEnemy(new Angel(*this, sf::Vector2f(WIDTH / 4.f, HEIGHT + 200.f)));
			EntityManager::GetInstance().SpawnEnemy(new Angel(*this, sf::Vector2f(WIDTH * 3.f / 4.f, HEIGHT + 200.f)));
		}

		AudioManager::GetInstance().PlayMusic(Music::BOSS_THEME);
	}
	else if ((_wave - 1) % 5 == 0)
	{
		AudioManager::GetInstance().StartMainTheme();
	}

	if (_wave % 5 != 0)
	{
		const float sideRandom = Random::GetFloat();

		for (int i = 0; i < number; ++i)
		{
			float x, y;

			if (sideRandom < 0.25f)
			{
				x = Random::GetFloat(0.f, WIDTH);
				y = Random::GetFloat(-100.f, -50.f);
			}
			else if (sideRandom < 0.5f)
			{
				x = Random::GetFloat(0.f, WIDTH);
				y = Random::GetFloat(HEIGHT + 50.f, HEIGHT + 100.f);
			}
			else if (sideRandom < 0.75f)
			{
				x = Random::GetFloat(-100.f, -50.f);
				y = Random::GetFloat(0.f, HEIGHT);
			}
			else
			{
				x = Random::GetFloat(WIDTH + 50.f, WIDTH + 100.f);
				y = Random::GetFloat(0.f, HEIGHT);
			}

			EntityManager::GetInstance().SpawnEnemy(new Camper(*this, sf::Vector2f(x, y)));
		}
	}
}

void Game::SetState(const GameState state)
{
	if (_state == state)
	{
		return;
	}

	if (state == GameState::PLAYING)
	{
		_gui = nullptr;

		if (_state == GameState::UPGRADE_CHOICE || _state == GameState::PAUSE)
		{
			AudioManager::GetInstance().ResumeAll();
		}
		else
		{
			EntityManager::GetInstance().GetPlayer()->TakeControl();
			AudioManager::GetInstance().StartMainTheme();
		}
	}
	else if (state == GameState::MAIN_MENU)
	{
		_gui = new MenuGui(*this);

		EntityManager::GetInstance().Restart(*this);

		_wave = 0;
		_waveTime = sf::Time::Zero;
		_waveDuration = sf::seconds(30.f);

		if (_state != GameState::DEAD)
		{
			AudioManager::GetInstance().PlayMusic(Music::DEATH);
		}
	}
	else if (state == GameState::WEAPON_CHOICE)
	{
		_gui = new WeaponChoiceGui(*this);
	}
	else if (state == GameState::DEAD)
	{
		_gui = new GameOverGui(*this);
		
		AudioManager::GetInstance().PlayMusic(Music::DEATH);

		EntityManager::GetInstance().EndGame();
	}
	else if (state == GameState::UPGRADE_CHOICE)
	{
		//_gui = new UpgradeChoiceGui(*this);

		AudioManager::GetInstance().PauseAll();
	}
	else if (state == GameState::PAUSE)
	{
		_gui = new PauseGui(*this);

		AudioManager::GetInstance().PauseAll();
	}

	_state = state;
}

void Game::Exit()
{
	_window.close();
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

bool Game::IsOutOfScreen(const sf::Vector2f position)
{
	return position.x < -100.f || position.x > Game::WIDTH + 100.f || position.y < -100.f || position.y > Game::HEIGHT + 100.f;
}
