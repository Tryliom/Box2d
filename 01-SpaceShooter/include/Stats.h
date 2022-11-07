#pragma once

namespace Stats
{
	struct EntityStats
	{
		float HealthRegeneration{ 0.f };
		float Speed{ 0.f };
		float MaxSpeed{ 0.f };
		float RotationSpeed{ 0.f };
		float CollisionDamage{ 0.f };
		float CollisionReductionDamage{ 0.f };
		float CollisionReductionDamagePercentage{ 0.f };
	};

	struct WeaponStats
	{
		float Damage{ 0.f };
		float DamagePercentage{ 0.f };
		float Speed{ 0.f };
		float SpeedPercentage{ 0.f };
		float Spread{ 0.f };
		float Range{ 0.f };
		int BulletsPerShot{ 0 };
		float BulletsPerShotPercentage{ 0.f };
		float Cooldown{ 0.f };
		float CooldownReduction{ 0.f };
		float CoolDownReductionPercentage{ 0.f };
	};
};