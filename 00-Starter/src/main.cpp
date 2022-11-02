#include "box2d/b2_body.h"
#include "box2d/b2_world.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_circle_shape.h"

#include "SFML/Graphics.hpp"
#include "Random.h"

constexpr float SCALE = 10.f;
constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

// Convert Box2D coordinates to SFML coordinates
sf::Vector2f b2ToSf(const b2Vec2& v)
{
	return sf::Vector2f(v.x * SCALE, HEIGHT - (v.y * SCALE));
}

// Convert SFML coordinates to Box2D coordinates
b2Vec2 sfToB2(const sf::Vector2f& v)
{
	return b2Vec2(v.x / SCALE, (HEIGHT - v.y) / SCALE);
}

int main()
{
	std::vector<b2Body*> bodies;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Box2D");

	window.setFramerateLimit(144);
	window.setVerticalSyncEnabled(true);

	b2Vec2 gravity(0.0f, -30.f);
	b2World world(gravity);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 3.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(WIDTH / SCALE, groundBodyDef.position.y);
	groundBody->CreateFixture(&groundBox, 2.0f);

	sf::RectangleShape ground(b2ToSf(groundBox.m_vertices[2]) - b2ToSf(groundBox.m_vertices[0]));
	ground.setOrigin(ground.getSize() / 2.0f);
	ground.setFillColor(sf::Color::Red);
	ground.setPosition(b2ToSf(groundBody->GetPosition()));

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position = sfToB2(sf::Vector2f(sf::Mouse::getPosition(window)));
			b2Body* body = world.CreateBody(&bodyDef);

			b2CircleShape dynamicBox;
			dynamicBox.m_radius = Random::GetFloat(0.5f, 2.0f);
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;
			fixtureDef.density = Random::GetFloat(10.f, 5000.f);
			fixtureDef.friction = Random::GetFloat(0.1f, 1.f);
			body->CreateFixture(&fixtureDef);

			bodies.push_back(body);
		}

		world.Step(1.0f / 60.0f, 8, 3);

		window.clear();
		window.draw(ground);

		for (auto body : bodies)
		{
			// Transform body into sfml rectangle shape and draw it
			b2Fixture* fixture = body->GetFixtureList();
			b2CircleShape* shape = static_cast<b2CircleShape*>(fixture->GetShape());

			sf::CircleShape circle(shape->m_radius * SCALE);
			circle.setOrigin(circle.getRadius(), circle.getRadius());
			circle.setFillColor(sf::Color::Green);
			circle.setPosition(b2ToSf(body->GetPosition()));
			circle.setOutlineColor(sf::Color::Black);
			circle.setOutlineThickness(-1.f);

			window.draw(circle);
		}

		window.display();
	}

	return 0;
}