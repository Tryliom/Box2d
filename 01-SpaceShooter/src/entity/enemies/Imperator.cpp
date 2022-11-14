#include "entity/enemies/Imperator.h"

#include "Assets.h"
#include "manager/AudioManager.h"
#include "weapon/weapons/Canon.h"
#include "weapon/weapons/MachineGun.h"
#include "weapon/weapons/Sniper.h"

Imperator::Imperator(Game& game, const sf::Vector2f position) :
	Enemy(game, position, Assets::GetInstance().GetTexture(Texture::ENEMY_IMPERATOR),
		500.f, 500.f, Group::ENEMY,
		Stats::EntityStats{
			.Speed = 1.f,
			.RotationSpeed = 10.f,
			.CollisionDamage = 20.f,
			.Size = 3.f
		},
		Stats::WeaponStats{
			.Damage = 10.f,
			.SpeedPercentage = -0.5f,
			.CooldownReductionPercentage = 0.5f,
			.Size = 5.f
		},
		{
			Pattern(ActionType::MOVE_TO_PLAYER, sf::seconds(3.f)),
			Pattern(ActionType::ATTACK, sf::seconds(2.f)),
		})
{
	_weapons = {
		new Canon(_weaponStats),
		new MachineGun(_weaponStats),
		new Sniper(_weaponStats)
	};
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
	else if (_currentWeaponIndex == 2)
	{
		_weaponStats = Stats::WeaponStats{
			.Size = 3.f
		};
	}
}

void Imperator::nextWeapon()
{
	_weapons[_currentWeaponIndex]->StopCharging();
	_currentWeaponIndex = (_currentWeaponIndex + 1) % _weapons.size();
	_weapon = _weapons[_currentWeaponIndex];
}

void Imperator::onDeath()
{
	AudioManager::GetInstance().PlaySound(Sound::BOSS_DEATH);
}
