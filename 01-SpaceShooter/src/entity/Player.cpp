#include "entity/Player.h"

#include <iostream>

#include "Assets.h"
#include "Game.h"
#include "module/modules/SparksModule.h"
#include "weapon/weapons/MachineGun.h"

Player::Player(Game& game) :
	Entity(
		game, {-100.f, Game::HEIGHT + 100.f}, Assets::GetInstance().GetTexture(Texture::SPACE_SHIP),
		100.f, Stats::EntityStats{
			.HealthRegeneration = 0.5f,
			.Speed = 800.f,
			.RotationSpeed = 25.f,
			.CollisionDamage = 20.f
		},
		Group::PLAYER
	)
{
	AddModule(new SparksModule());

	// Set the angle of the ship to look to the middle of the screen
	const auto position = sf::Vector2f(Game::WIDTH / 2.f, Game::HEIGHT / 2.f) - _shape.getPosition();

	_shape.setRotation(Game::RadToDegree(atan2(position.y, position.x)) + 90.f);
	_body->SetTransform(Game::PixelToMeter(_shape.getPosition()), Game::DegreeToRad(_shape.getRotation()));

	ReleaseControl();
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

void Player::onLevelUp()
{
	_xp -= GetMaxXp();
	_level++;
	_credits++;
}

void Player::Update(const sf::Time elapsed)
{
	Entity::Update(elapsed);
	
	_tailCooldown += elapsed;

	if (_copilot)
	{
		Move(elapsed);

		// If the player is on the center of the screen, stop it
		if (_shape.getPosition().x >= Game::WIDTH / 2.f)
		{
			_body->SetLinearVelocity({ 0.f, 0.f });
		}

		TryToShoot();
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
	_invincible = false;

	ChargeWeapon();
}

void Player::ReleaseControl()
{
	_copilot = true;
	_invincible = true;
}

bool Player::IsAlive() const
{
	return _health > 0.f;
}

bool Player::IsCopilot() const
{
	return _copilot;
}

int Player::GetMaxXp() const
{
	return 100 + _level * 25;
}

float Player::GetXpPercentage() const
{
	return static_cast<float>(_xp) / static_cast<float>(GetMaxXp());
}

bool Player::HasCredits() const
{
	return _credits > 0;
}

void Player::UseCredit()
{
	_credits--;
}

void Player::Contact(const XpShard* xpShard)
{
	_xp += xpShard->GetXp();

	bool hasLevelUp = false;

	while (_xp >= GetMaxXp())
	{
		onLevelUp();

		hasLevelUp = true;
	}

	if (hasLevelUp)
	{
		_game.SetState(GameState::UPGRADE_CHOICE);
	}
}

void Player::TryToShoot()
{
	if (_weapon != nullptr && _weapon->CanShoot())
	{
		_weapon->Shoot(this, GetProjectileGroup());

		ChargeWeapon();
	}
}

int Player::GetCredits() const
{
	return _credits;
}
