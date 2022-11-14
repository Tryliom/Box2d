#include "entity/enemies/Angel.h"

#include "Assets.h"
#include "Random.h"
#include "module/modules/SparksModule.h"
#include "weapon/weapons/Sniper.h"

Angel::Angel(Game& game, sf::Vector2f position) :
	Enemy(game, position, Assets::GetInstance().GetTexture(Texture::ENEMY_ANGEL),
		150.f, 150.f, Group::ENEMY,
		Stats::EntityStats{
			.Speed = 200.f,
			.RotationSpeed = 10.f,
			.CollisionDamage = 5.f,
			.Size = .5f
		},
		Stats::WeaponStats{
			.DamagePercentage = -0.5f,
			.CooldownReductionPercentage = -0.7f
		},
		{
			Pattern(ActionType::MOVE_AROUND_PLAYER, sf::seconds(Random::GetFloat(3.5f, 5.f))),
			Pattern(ActionType::ROTATE, sf::seconds(Random::GetFloat(0.5f, 2.f))),
			Pattern(ActionType::ATTACK, sf::seconds(Random::GetFloat(1.5f, 3.f)))
		})
{
	_weapon = new Sniper(_weaponStats);
	AddModule(new SparksModule());
}
