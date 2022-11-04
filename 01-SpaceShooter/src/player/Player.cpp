#include "player/Player.h"

#include "Assets.h"

Player::Player(Game& game, const sf::Vector2f position) : DrawableObject(game.GetNewBody(), position), _game(game)
{
	_health = 100;
	_maxHealth = 100;

	_speed = 20.0f;
	_rotationSpeed = 0.5f;
	_maxSpeed = 100.0f;
	_sparksPerSecond = 5;

	const sf::Texture texture = Assets::GetInstance().GetTexture(Texture::SPACE_SHIP);

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
	fixtureDef.friction = 0.1f;

	_body->CreateFixture(&fixtureDef);
	_body->SetAngularDamping(10.f);

	_body->SetTransform(Game::PixelToMeter(position), Game::sfAngleToB2Angle(_shape.getRotation()));

	// Add a linear velocity to the body to make it move to the angle it is facing by default to add some style
	_body->SetLinearVelocity(b2Vec2(cos(_body->GetAngle()) * _speed, sin(_body->GetAngle()) * _speed));
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape, states);

	for (const auto& trail : _trails)
	{
		target.draw(trail, states);
	}
}

void Player::Update(const sf::Time elapsed)
{
	_trailCooldown += elapsed;

	// Make the player rotate slowly to the mouse position
	const auto mousePosition = sf::Vector2f(sf::Mouse::getPosition(_game.GetWindow()));
	const sf::Vector2f direction = mousePosition - _shape.getPosition();
	const float angle = atan2(direction.y, direction.x) * 180 / b2_pi;

	_body->SetAngularVelocity(Game::sfAngleToB2Angle(angle - _shape.getRotation()) * _rotationSpeed);

	for (auto& trail : _trails)
	{
		trail.UpdatePosition(_shape.getPosition(), _shape.getRotation());
		trail.Update(elapsed);
	}

	// Update the position of the player
	_shape.setPosition(Game::MeterToPixel(_body->GetPosition()));

	// Update the rotation of the player
	_shape.setRotation(Game::b2AngleToSfAngle(_body->GetAngle()));
}

void Player::Move()
{
	// If the player is moving, create a trail and sparks
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		_body->ApplyForceToCenter(b2Vec2(_speed * cos(_body->GetAngle()), _speed * sin(_body->GetAngle())), true);

		if (_trailCooldown >= sf::Time(sf::seconds(TRAIL_COOLDOWN)))
		{
			_trailCooldown = sf::Time::Zero;

			_trails.emplace_back(Trail(_game.GetNewBody(), _shape.getPosition(), _shape.getRotation()));

			_game.PlaySound(Sound::BURST);
		}
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
