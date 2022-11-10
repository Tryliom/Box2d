#include "entity/enemies/Camper.h"

#include "Assets.h"
#include "weapon/weapons/Canon.h"

Camper::Camper(Game& game, sf::Vector2f position) :
	Enemy(game, position, Assets::GetInstance().GetTexture(Texture::ENEMY_CAMPER),
		30.f, 30.f, Group::ENEMY, 
		Stats::EntityStats{
			.Speed = 0.05f,
			.RotationSpeed = 5.f,
			.CollisionDamage = 10.f,
		},
		Stats::WeaponStats{
			.CooldownReductionPercentage = -0.7f
		},
		{
			Pattern(ActionType::MOVE_TO_PLAYER, sf::seconds(5.f)),
			Pattern(ActionType::ATTACK, sf::seconds(2.f)),
		})
{
	_weapon = new Canon(_weaponStats);
}
