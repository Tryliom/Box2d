#pragma once
#include "SFML/Graphics.hpp"

#include "ContactListener.h"
#include "box2d/b2_world.h"
#include "gui/Gui.h"

enum class GameState
{
	NONE,
	PLAYING,
	MAIN_MENU,
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

	int _wave{ 0 };
	sf::Time _waveTime{ sf::Time::Zero };
	sf::Time _waveDuration{ sf::seconds(30.f) };

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

	int Loop();

	b2Body* GetNewBody();

	sf::RenderWindow& GetWindow() { return _window; }
	b2World& GetWorld() { return _world; }

	void SetState(GameState state);

	static bool IsOutOfScreen(sf::Vector2f position);
};
