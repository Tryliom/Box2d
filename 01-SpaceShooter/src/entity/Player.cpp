#include "entity/Player.h"

#include "Assets.h"
#include "Game.h"
#include "Random.h"
#include "module/modules/SparksModule.h"
#include "weapon/weapons/Canon.h"

Player::Player(Game& game, const sf::Vector2f position) :
	Entity(
		game, position, Assets::GetInstance().GetTexture(Texture::SPACE_SHIP),
		100.f, 100.f, Stats::EntityStats{
			.HealthRegeneration = 0.5f,
			.Speed = 0.5f,
			.RotationSpeed = 15.f,
		},
		Group::PLAYER, nullptr, 45.f
	)
{
	_weapon = new Canon(_weaponStats);
	AddModule(new SparksModule());

	// Add a linear velocity to the body to make it move to the angle it is facing by default to add some style
	_body->SetLinearVelocity(Game::GetLinearVelocity(GetTotalStats().GetSpeed() * 100.f, _shape.getRotation()));
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	for (const auto& trail : _tails)
	{
		target.draw(trail, states);
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

void Player::Update(const sf::Time elapsed)
{
	Entity::Update(elapsed);

	_tailCooldown += elapsed;

	// Make the player rotate slowly to the mouse position angle
	const auto mousePosition = sf::Vector2f(sf::Mouse::getPosition(_game.GetWindow()));
	const auto playerPosition = _shape.getPosition();
	const auto position = mousePosition - playerPosition;

	// Get angle between two positions
	const float angle = Game::RadToDegree(atan2(position.y, position.x));

	rotate(angle);

	for (auto& tail : _tails)
	{
		// Update the position of the trail at the bottom of the ship
		tail.Update(elapsed);
		tail.SetAngle(_shape.getRotation());
		tail.SetPosition(getTrailPosition());
	}

	if (_weapon != nullptr)
	{
		_weapon->UpdatePosition(_shape.getPosition());
		_weapon->Update(elapsed);
	}

	// Remove tails that are dead
	_tails.erase(std::remove_if(_tails.begin(), _tails.end(), [](const Tail& tail) { return tail.IsDead(); }), _tails.end());
}

void Player::Move()
{
	Entity::Move();

	if (_tailCooldown >= sf::Time(sf::seconds(TAIL_COOLDOWN)))
	{
		_tailCooldown = sf::Time::Zero;

		_tails.emplace_back(Tail(getTrailPosition(), _shape.getRotation()));
	}
}