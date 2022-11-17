#include "entity/enemies/Camper.h"

#include "Assets.h"
#include "Random.h"
#include "weapon/weapons/Canon.h"

Camper::Camper(Game& game, sf::Vector2f position, int level) :
	Enemy(game, position, Assets::GetInstance().GetTexture(Texture::ENEMY_CAMPER),
		30.f + level * 5.f,
		30 + level * 5,
		Group::ENEMY, 
		Stats::EntityStats{
			.Speed = 100.f + level * 10.f,
			.RotationSpeed = 5.f + level * 0.5f,
			.CollisionDamage = 10.f + level * 2.f,
		},
		Stats::WeaponStats{
			.DamagePercentage = -0.5f,
			.BulletsPerShotPercentage = level * 0.5f,
			.CooldownReductionPercentage = -0.7f,
		},
		{
			Pattern(ActionType::MOVE_AROUND_PLAYER, sf::seconds(Random::GetFloat(3.5f, 5.f))),
			Pattern(ActionType::ATTACK, sf::seconds(Random::GetFloat(1.5f, 3.f)))
		})
{
	_weapon = new Canon(this);
}
