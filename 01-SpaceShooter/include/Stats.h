#pragma once

namespace Stats
{
	struct EntityStats
	{
		float HealthRegeneration{ 0.f };
		float HealthRegenerationPercentage{ 0.f };

		float Speed{ 0.f };
		float SpeedPercentage{ 0.f };

		float RotationSpeed{ 0.f };

		float CollisionDamage{ 0.f };
		float CollisionDamagePercentage{ 0.f };

		float CollisionReductionDamage{ 0.f };
		float CollisionReductionDamagePercentage{ 0.f };

		float Size{ 0.f };

		float GetHealthRegeneration() const;
		float GetSpeed() const;
		float GetMaxSpeed() const;
		float GetRotationSpeed() const;
		float GetCollisionDamage() const;
		float GetCollisionReductionDamage() const;
		float GetCollisionDamage(float collisionDamage) const;
		float GetSize() const;
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

		float Size{ 0.f };

		float GetDamage() const;
		float GetSpeed() const;
		float GetSpread() const;
		float GetRange() const;
		int GetBulletsPerShot() const;
		float GetCooldown() const;
		float GetSize() const;
	};

	WeaponStats operator+(WeaponStats stats, WeaponStats otherStats);
	EntityStats operator+(EntityStats stats, EntityStats otherStats);
	WeaponStats operator+=(WeaponStats stats, WeaponStats otherStats);
	EntityStats operator+=(EntityStats stats, EntityStats otherStats);
};