#pragma once
#include "SFML/Graphics.hpp"

#include "ContactListener.h"
#include "box2d/b2_world.h"
#include "gui/Gui.h"
#include "manager/WaveManager.h"

enum class GameState
{
	NONE,
	PAUSE,
	PLAYING,
	MAIN_MENU,
	WEAPON_CHOICE,
	UPGRADE_CHOICE,
	DEAD
};

class Game final
{
public:
	Game();

private:
	// Game display and physics
	sf::RenderWindow _window;
	b2World _world;
	ContactListener _contactListener;

	// Gui
	Gui* _gui{ nullptr };
	GameState _state = GameState::NONE;

	sf::RectangleShape _background;
	float _backgroundStep;

	WaveManager _waveManager;

	void update(sf::Time elapsed);
	void checkInputs(sf::Event event);
	void render();
	void spawnEnemies();

public:
	inline static float HEIGHT = 0.f;
	inline static float WIDTH = 0.f;
	inline static float SCALE = 100.0f;

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

	static b2Vec2 GetLinearVelocity(float speed, float angleDegree);

	static bool IsOutOfScreen(sf::Vector2f position);

	int Loop();

	b2Body* GetNewBody();

	sf::RenderWindow& GetWindow() { return _window; }
	b2World& GetWorld() { return _world; }

	void SetState(GameState state);

	void Exit();
};
