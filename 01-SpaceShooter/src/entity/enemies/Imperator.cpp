#include "entity/enemies/Imperator.h"

#include "Assets.h"
#include "weapon/weapons/Canon.h"
#include "weapon/weapons/MachineGun.h"
#include "weapon/weapons/Sniper.h"

Imperator::Imperator(Game& game, sf::Vector2f position) :
	Enemy(game, position, Assets::GetInstance().GetTexture(Texture::ENEMY_IMPERATOR),
		150.f, 150.f, Group::ENEMY,
		Stats::EntityStats{
			.Speed = 0.1f,
			.RotationSpeed = 10.f,
			.CollisionDamage = 20.f,
			.Size = 2.f
		},
		Stats::WeaponStats{
			.SpeedPercentage = -0.5f
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
			weapon->UpdatePosition(GetPosition());
			weapon->Update(elapsed);
		}
	}
}

void Imperator::draw(sf::RenderTarget& target, sf::RenderStates states) const
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
}

void Imperator::nextWeapon()
{
	_weapons[_currentWeaponIndex]->StopCharging();
	_currentWeaponIndex = (_currentWeaponIndex + 1) % _weapons.size();
	_weapon = _weapons[_currentWeaponIndex];
}
