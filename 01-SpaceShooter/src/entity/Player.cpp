#include "entity/Player.h"

#include <iostream>

#include "Assets.h"
#include "Game.h"
#include "module/modules/SparksModule.h"
#include "weapon/weapons/MachineGun.h"

Player::Player(Game& game) :
	Entity(
		game, {-100.f, Game::HEIGHT + 100.f}, Assets::GetInstance().GetTexture(Texture::SPACE_SHIP),
		100.f, 100.f, Stats::EntityStats{
			.HealthRegeneration = 0.5f,
			.Speed = 600.f,
			.RotationSpeed = 15.f,
			.CollisionDamage = 20.f
		},
		Group::PLAYER
	)
{
	_weapon = new MachineGun(_weaponStats);
	AddModule(new SparksModule());

	// Temporary
	_weaponStats = Stats::WeaponStats{
		.DamagePercentage = 0.5f,
		.BulletsPerShotPercentage = 1.f,
		.CooldownReductionPercentage = 0.7f,
		.Size = 1.f
	};

	// Set the angle of the ship to the middle of the screen
	const auto position = sf::Vector2f(Game::WIDTH / 2.f, Game::HEIGHT / 2.f) - _shape.getPosition();

	_shape.setRotation(Game::RadToDegree(atan2(position.y, position.x)) + 90.f);
	_body->SetTransform(Game::PixelToMeter(_shape.getPosition()), Game::DegreeToRad(_shape.getRotation()));
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	for (const auto& tail : _tails)
	{
		target.draw(tail, states);
	}

	Entity::draw(target, states);
}

sf::Vector2f Player::getTailPosition() const
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

	if (_copilot)
	{
		Move(elapsed);

		// Set the linear velocity to go to the center of the screen
		const float x = Game::WIDTH / 2.f - _shape.getPosition().x;
		const float y = Game::HEIGHT / 2.f - _shape.getPosition().y;
		const float speedToCenter = (x * x + y * y) / Game::SCALE;

		_body->SetLinearVelocity(Game::GetLinearVelocity(speedToCenter * elapsed.asSeconds(), Game::RadToDegree(_body->GetAngle())));

		// If the player is on the center of the screen, stop it
		if (_shape.getPosition().y <= Game::HEIGHT / 2.f || _shape.getPosition().y <= Game::HEIGHT / 2.f)
		{
			_body->SetLinearVelocity({ 0.f, 0.f });
		}
	}
	else
	{
		// Make the player rotate slowly to the mouse position angle
		const auto mousePosition = sf::Vector2f(sf::Mouse::getPosition(_game.GetWindow()));
		const auto playerPosition = _shape.getPosition();
		const auto position = mousePosition - playerPosition;

		// Get angle between two positions
		const float angle = Game::RadToDegree(atan2(position.y, position.x));

		rotate(angle);
	}

	for (auto& tail : _tails)
	{
		// Update the position of the trail at the bottom of the ship
		tail.Update(elapsed);
		tail.SetAngle(_shape.getRotation());
		tail.SetPosition(getTailPosition());
	}

	// Remove tails that are dead
	std::erase_if(_tails, [](const Tail& tail) { return tail.IsDead(); });
}

void Player::Move(sf::Time elapsed)
{
	Entity::Move(elapsed);

	if (_tailCooldown >= sf::Time(sf::seconds(TAIL_COOLDOWN)))
	{
		_tailCooldown = sf::Time::Zero;

		_tails.emplace_back(Tail(getTailPosition(), _shape.getRotation()));
	}
}

void Player::TakeControl()
{
	_copilot = false;
}

bool Player::IsAlive() const
{
	return _health > 0.f;
}
