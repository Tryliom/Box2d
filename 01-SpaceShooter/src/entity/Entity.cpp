#include "entity/Entity.h"

#include "Game.h"

Entity::Entity(b2Body* body, const sf::Vector2f position, const sf::Texture& texture,
               const float health, const float maxHealth, const float healthRegeneration,
               const float speed, const float rotationSpeed, const float maxSpeed, const float angle) :
	DrawableObject(body, position)
{
	_health = health;
	_maxHealth = maxHealth;
	_healthRegeneration = healthRegeneration;

	_speed = speed;
	_rotationSpeed = rotationSpeed;
	_maxSpeed = maxSpeed;

	_shape.setTexture(&texture);
	_shape.setSize(sf::Vector2f(texture.getSize()));
	_shape.setOrigin(_shape.getSize() / 2.f);
	_shape.setPosition(position);
	_shape.setRotation(angle);

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
}

void Entity::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_shape, states);
}

float Entity::getDeltaAngle(const float angle) const
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

void Entity::rotate(float angle) const
{
	angle = getDeltaAngle(angle);

	if (angle > _rotationSpeed)
	{
		angle = _rotationSpeed;
	}
	else if (angle < -_rotationSpeed)
	{
		angle = -_rotationSpeed;
	}

	_body->SetAngularVelocity(Game::DegreeToRad(angle * 10.f));
}

void Entity::Update(const sf::Time elapsed)
{
	if (_health < _maxHealth)
	{
		_health += _healthRegeneration * elapsed.asSeconds();
	}

	if (_health > _maxHealth)
	{
		_health = _maxHealth;
	}

	// Update the position of the shape
	_shape.setPosition(Game::MeterToPixel(_body->GetPosition()));

	// Update the rotation of the shape
	_shape.setRotation(Game::RadToDegree(_body->GetAngle()));
}

void Entity::Move()
{
	// Add a linear velocity to the body to make it move to the angle it is facing
	if (_body->GetLinearVelocity().Length() < _maxSpeed)
	{
		_body->SetLinearVelocity(_body->GetLinearVelocity() + Game::GetLinearVelocity(_speed, Game::RadToDegree(_body->GetAngle())));
	}
}

sf::Vector2f Entity::GetPosition() const
{
	return Game::MeterToPixel(_body->GetPosition());
}

void Entity::SetPosition(const sf::Vector2f position)
{
	_body->SetTransform(Game::PixelToMeter(position), _body->GetAngle()); _shape.setPosition(position);
}

void Entity::TakeDamage(const float damage)
{
	_health -= damage;
}

void Entity::StartAttackAnimation()
{
	_attackCharge = AttackCharge(_shape.getPosition(), (_shape.getSize().x + _shape.getSize().y) / 2.f, 5.f);
}

void Entity::StopAttackAnimation()
{
	_attackCharge.Stop();
}
