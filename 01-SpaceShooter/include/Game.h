#pragma once
#include "entity/Player.h"
#include "Assets.h"

#include "SFML/Graphics.hpp"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>

#include "ContactListener.h"
#include "box2d/b2_body.h"
#include "box2d/b2_world.h"
#include "entity/Enemy.h"
#include "manager/AnimationManager.h"
#include "manager/ProjectileManager.h"

class Game final
{
public:
	Game();

private:
	sf::RenderWindow _window;
	b2World _world;
	sf::Music _music;
	std::vector<sf::Sound> _sounds;
	ContactListener _contactListener;

	sf::Sound _burstSound;
	bool _stopBurstSound;

	sf::RectangleShape _background;
	float _backgroundStep;

	// Entities
	Player _player;
	std::list<Enemy*> _enemies;

	int _wave{ 0 };
	sf::Time _waveTime{ sf::Time::Zero };
	sf::Time _waveDuration{ sf::seconds(30.f) };

	void update(sf::Time elapsed);
	void checkInputs(sf::Event event);
	void render();
	void renderHealthBar();
	void spawnEnemies();

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

	static b2Vec2 GetLinearVelocity(float speed, float angleDegree);

	int Loop();

	b2Body* GetNewBody();
	Player& GetPlayer();

	sf::RenderWindow& GetWindow() { return _window; }
	b2World& GetWorld() { return _world; }

	void PlaySound(Sound sound);
	static bool IsOutOfScreen(sf::Vector2f position);
};
