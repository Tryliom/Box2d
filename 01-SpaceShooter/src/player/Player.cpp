#include "player/Player.h"

#include <iostream>

#include "Assets.h"
#include "Game.h"

Player::Player(Game& game, const sf::Vector2f position) : DrawableObject(game.GetNewBody(), position), _game(game)
{
	_health = 100.f;
	_maxHealth = 100.f;
	_healthRegeneration = 0.5f;

	_speed = 0.5f;
	_rotationSpeed = 15.f;
	_maxSpeed = 2000.0f;
	_sparksPerSecond = 5;

	const sf::Texture& texture = Assets::GetInstance().GetTexture(Texture::SPACE_SHIP);

	_shape.setTexture(&texture);
	_shape.setSize(sf::Vector2f(texture.getSize()));
	_shape.setOrigin(_shape.getSize() / 2.f);
	_shape.setPosition(position);
	_shape.setRotation(90.f);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(Game::PixelToMeter(_shape.getSize().x / 2.f), Game::PixelToMeter(_shape.getSize().y / 2.f));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.restitution = 0.1f;
	fixtureDef.friction = 0.5f;

	_body->CreateFixture(&fixtureDef);

	_body->SetLinearDamping(0.5f);
	_body->SetTransform(Game::PixelToMeter(position), Game::DegreeToRad(_shape.getRotation()));
	_body->SetType(b2_dynamicBody);
	_body->SetBullet(true);

	// Add a linear velocity to the body to make it move to the angle it is facing by default to add some style
	_body->SetLinearVelocity(b2Vec2(cos(_body->GetAngle()) * 10.0f, sin(_body->GetAngle()) * 10.0f));
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_shape, states);

	for (const auto& trail : _trails)
	{
		target.draw(trail, states);
	}

	// Draw health bar
	sf::RectangleShape healthBackgroundBar;
	healthBackgroundBar.setSize(sf::Vector2f(400.f, 8.f));
	healthBackgroundBar.setFillColor(sf::Color(40, 40, 40));
	healthBackgroundBar.setOrigin(healthBackgroundBar.getSize() / 2.f);
	healthBackgroundBar.setPosition({ Game::WIDTH / 2.f, Game::HEIGHT - 20.f });

	target.draw(healthBackgroundBar, states);

	float healthPercentage = _health / _maxHealth;

	if (healthPercentage < 0.f)
	{
		healthPercentage = 0.f;
	}

	sf::RectangleShape healthBar;
	healthBar.setSize(sf::Vector2f(healthBackgroundBar.getSize().x * _health / _maxHealth, healthBackgroundBar.getSize().y));
	healthBar.setFillColor(sf::Color::Red);
	healthBackgroundBar.setOutlineColor(sf::Color::Black);
	healthBackgroundBar.setOutlineThickness(-0.5f);
	healthBar.setOrigin(healthBar.getSize() / 2.f);
	healthBar.setPosition(healthBackgroundBar.getPosition());

	target.draw(healthBar, states);
}

float Player::getNearestAngle(const float angle) const
{
	const float currentAngle = Game::RadToDegree(_body->GetAngle());
	float difference = angle - currentAngle;

	while (difference < -180.f)
	{
		difference += 360.f;
	}

	while (difference > 180.f)
	{
		difference -= 360.f;
	}

	return difference + 90.f;
}

sf::Vector2f Player::getTrailPosition() const
{
	// Calculate the difference of angle between the default one and the current one
	const float angle = Game::RadToDegree(_body->GetAngle()) - 90.f;

	// Calculate the position of the trail
	const float x = _shape.getPosition().x - (_shape.getSize().x / 5.f) * std::cos(Game::DegreeToRad(angle));
	const float y = _shape.getPosition().y - (_shape.getSize().y / 5.f) * std::sin(Game::DegreeToRad(angle));

	return { x, y };
}

void Player::Update(const sf::Time elapsed)
{
	if (_health < _maxHealth)
	{
		_health += _healthRegeneration * elapsed.asSeconds();
	}

	if (_health > _maxHealth)
	{
		_health = _maxHealth;
	}

	_trailCooldown += elapsed;

	// Make the player rotate slowly to the mouse position angle
	const auto mousePosition = sf::Vector2f(sf::Mouse::getPosition(_game.GetWindow()));
	const auto playerPosition = _shape.getPosition();
	const auto position = mousePosition - playerPosition;

	// Get angle between two positions
	const float angle = Game::RadToDegree(atan2(position.y, position.x));

	// Get the nearest angle to the mouse position
	float targetAngle = getNearestAngle(angle);

	if (abs(targetAngle) > _rotationSpeed)
	{
		targetAngle = targetAngle > 0 ? _rotationSpeed : -_rotationSpeed;
	}

	// Rotate the player
	_body->SetAngularVelocity(Game::DegreeToRad(targetAngle * 10.f));

	for (auto& trail : _trails)
	{
		// Update the position of the trail at the bottom of the ship
		trail.Update(elapsed);
		trail.GetBody()->SetAngularVelocity(_body->GetAngularVelocity());
		trail.GetBody()->SetLinearVelocity(_body->GetLinearVelocity());
	}

	// Update the position of the player
	_shape.setPosition(Game::MeterToPixel(_body->GetPosition()));

	// Update the rotation of the player
	_shape.setRotation(Game::RadToDegree(_body->GetAngle()));

	// Remove trails that are dead
	_trails.erase(std::remove_if(_trails.begin(), _trails.end(), [](const Trail& trail) { return trail.IsDead(); }), _trails.end());
}

void Player::Move()
{
	// Add a linear velocity to the body to make it move to the angle it is facing
	if (_body->GetLinearVelocity().Length() < _maxSpeed)
	{
		const float angle = Game::DegreeToRad(Game::RadToDegree(_body->GetAngle()) - 90.f);
		const float x = _speed * std::cos(angle);
		const float y = _speed * std::sin(angle);

		_body->SetLinearVelocity(_body->GetLinearVelocity() + b2Vec2(x, - y));
	}

	if (_trailCooldown >= sf::Time(sf::seconds(TRAIL_COOLDOWN)))
	{
		_trailCooldown = sf::Time::Zero;

		_trails.emplace_back(Trail(_game.GetNewBody(), getTrailPosition(), _shape.getRotation()));
	}
}

sf::Vector2f Player::GetPosition() const
{
	return Game::MeterToPixel(_body->GetPosition());
}

void Player::SetPosition(const sf::Vector2f position)
{
	_body->SetTransform(Game::PixelToMeter(position), _body->GetAngle()); _shape.setPosition(position);
}

void Player::TakeDamage(const float damage)
{
	_health -= damage;
}
