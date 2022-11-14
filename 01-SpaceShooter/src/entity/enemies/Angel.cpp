#include "entity/enemies/Angel.h"

#include "Assets.h"
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
			Pattern(ActionType::MOVE_AROUND_PLAYER, sf::seconds(5.f)),
			Pattern(ActionType::ROTATE, sf::seconds(2.f)),
			Pattern(ActionType::ATTACK, sf::seconds(2.f))
		})
{
	_weapon = new Sniper(_weaponStats);
	AddModule(new SparksModule());
}
