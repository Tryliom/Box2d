#include "entity/Player.h"

#include "Assets.h"
#include "Game.h"
#include "Random.h"
#include "weapon/weapons/Canon.h"

Player::Player(Game& game, const sf::Vector2f position) :
	Entity(
		game, position, Assets::GetInstance().GetTexture(Texture::SPACE_SHIP),
		100.f, 100.f, 0.5f, 0.5f, 15.f, 2000.f,
		Group::PLAYER, new Canon(), 45.f
	)
{
	_damage = 10.f;
	_sparksPerSecond = 20.f;
	_sparksAngle = 90.f;

	// Add a linear velocity to the body to make it move to the angle it is facing by default to add some style
	_body->SetLinearVelocity(Game::GetLinearVelocity(_speed * 100.f, _shape.getRotation()));
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	for (const auto& trail : _trails)
	{
		target.draw(trail, states);
	}

	for (const auto& sparks : _sparks)
	{
		target.draw(sparks, states);
	}

	if (_weapon != nullptr)
	{
		target.draw(*_weapon, states);
	}

	Entity::draw(target, states);
}

sf::Vector2f Player::getTrailPosition() const
{
	const float angle = Game::RadToDegree(_body->GetAngle()) - 90.f;

	// Calculate the position of the trail
	const float x = _shape.getPosition().x - (_shape.getSize().x / 5.f) * std::cos(Game::DegreeToRad(angle));
	const float y = _shape.getPosition().y - (_shape.getSize().y / 5.f) * std::sin(Game::DegreeToRad(angle));

	return { x, y };
}

void Player::AddSparks(float angleDegree)
{
	// Calculate the position of the sparks
	const float x = _shape.getPosition().x - (_shape.getSize().x / 5.f) * std::cos(Game::DegreeToRad(angleDegree));
	const float y = _shape.getPosition().y - (_shape.getSize().y / 5.f) * std::sin(Game::DegreeToRad(angleDegree));
	
	const float sparksSpeed = _speed * 50.f;
	angleDegree -= 90.f;

	_sparks.emplace_back(Sparks(_game.GetNewBody(), sf::Vector2f(x, y), angleDegree, Game::GetLinearVelocity(sparksSpeed, angleDegree), _damage));
}

void Player::Update(const sf::Time elapsed)
{
	_trailCooldown += elapsed;
	_sparksCooldown += elapsed;

	// Make the player rotate slowly to the mouse position angle
	const auto mousePosition = sf::Vector2f(sf::Mouse::getPosition(_game.GetWindow()));
	const auto playerPosition = _shape.getPosition();
	const auto position = mousePosition - playerPosition;

	// Get angle between two positions
	const float angle = Game::RadToDegree(atan2(position.y, position.x));

	rotate(angle);

	for (auto& trail : _trails)
	{
		// Update the position of the trail at the bottom of the ship
		trail.Update(elapsed);
		trail.GetBody()->SetAngularVelocity(_body->GetAngularVelocity());
		trail.GetBody()->SetLinearVelocity(_body->GetLinearVelocity());
	}

	for (auto& sparks : _sparks)
	{
		sparks.Update(elapsed);
	}

	if (_weapon != nullptr)
	{
		_weapon->UpdatePosition(_shape.getPosition());
		_weapon->Update(elapsed);
	}

	// Remove trails that are dead
	_trails.erase(std::remove_if(_trails.begin(), _trails.end(), [](const Tail& trail) { return trail.IsDead(); }), _trails.end());

	// Remove sparks that are dead
	_sparks.erase(std::remove_if(_sparks.begin(), _sparks.end(), [](const Sparks& sparks) { return sparks.IsDead(); }), _sparks.end());

	Entity::Update(elapsed);
}

void Player::Move()
{
	Entity::Move();

	if (_trailCooldown >= sf::Time(sf::seconds(TRAIL_COOLDOWN)))
	{
		_trailCooldown = sf::Time::Zero;

		_trails.emplace_back(Tail(_game.GetNewBody(), getTrailPosition(), _shape.getRotation(), _damage));
	}

	if (_sparksCooldown >= sf::Time(sf::seconds(1.f / _sparksPerSecond)))
	{
		_sparksCooldown = sf::Time::Zero;

		const float anglePosition = Game::RadToDegree(_body->GetAngle()) - 90.f;

		AddSparks(Random::GetFloat(anglePosition - _sparksAngle / 2.f, anglePosition));
		AddSparks(Random::GetFloat(anglePosition, anglePosition + _sparksAngle / 2.f));
	}
}