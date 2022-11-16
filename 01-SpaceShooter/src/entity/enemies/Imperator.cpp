#include "entity/enemies/Imperator.h"

#include "Assets.h"
#include "weapon/weapons/Canon.h"
#include "weapon/weapons/MachineGun.h"

Imperator::Imperator(Game& game, const sf::Vector2f position, int level) :
	Enemy(game, position, Assets::GetInstance().GetTexture(Texture::ENEMY_IMPERATOR),
		500.f + level * 100.f, Group::ENEMY,
		Stats::EntityStats{
			.Speed = 50.f + 10.f * level,
			.RotationSpeed = 10.f + level,
			.CollisionDamage = 20.f + level * 2.f,
			.Size = 3.f + level * 0.2f,
		},
		Stats::WeaponStats{
			.Damage = 10.f,
			.SpeedPercentage = -0.5f,
			.CooldownReductionPercentage = 0.5f,
			.Size = 5.f,
		},
		{
			Pattern(ActionType::MOVE_AROUND_PLAYER, sf::seconds(3.f)),
			Pattern(ActionType::ROTATE, sf::seconds(1.f)),
			Pattern(ActionType::ATTACK, sf::seconds(2.f)),
		})
{
	_weapons = {
		new Canon(_weaponStats),
		new MachineGun(_weaponStats)
	};

	_weapon = _weapons[_currentWeaponIndex];
}

void Imperator::Update(const sf::Time elapsed)
{
	Enemy::Update(elapsed);

	for (const auto weapon : _weapons)
	{
		if (weapon != _weapons[_currentWeaponIndex])
		{
			weapon->UpdatePosition(this);
			weapon->Update(elapsed);
		}
	}
}

void Imperator::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	Enemy::draw(target, states);

	for (const auto weapon : _weapons)
	{
		target.draw(*weapon);
	}
}

void Imperator::onEndCycle()
{
	// Change weapon
	nextWeapon();

	if (_currentWeaponIndex == 0)
	{
		_weaponStats = Stats::WeaponStats{
			.Damage = 10.f,
			.SpeedPercentage = -0.5f,
			.CooldownReductionPercentage = 0.5f,
			.Size = 5.f
		};
	}
	else if (_currentWeaponIndex == 1)
	{
		_weaponStats = Stats::WeaponStats{
			.Damage = -4.f,
			.SpeedPercentage = -0.5f,
			.Spread = 10.f,
			.BulletsPerShotPercentage = 3.f,
			.CooldownReductionPercentage = 0.5f
		};
	}
}

void Imperator::nextWeapon()
{
	_weapons[_currentWeaponIndex]->StopCharging();
	_currentWeaponIndex = (_currentWeaponIndex + 1) % _weapons.size();
	_weapon = _weapons[_currentWeaponIndex];
}
