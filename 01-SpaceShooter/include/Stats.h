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

		[[nodiscard]] float GetHealthRegeneration() const;
		[[nodiscard]] float GetSpeed() const;
		[[nodiscard]] float GetMaxSpeed() const;
		[[nodiscard]] float GetRotationSpeed() const;
		[[nodiscard]] float GetCollisionDamage() const;
		[[nodiscard]] float GetCollisionReductionDamage() const;
		[[nodiscard]] float GetCollisionDamage(float collisionDamage) const;
		[[nodiscard]] float GetSize() const;
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
		float CooldownReductionPercentage{ 0.f };

		float Size{ 0.f };

		[[nodiscard]] float GetDamage() const;
		[[nodiscard]] float GetSpeed() const;
		[[nodiscard]] float GetSpread() const;
		[[nodiscard]] float GetRange() const;
		[[nodiscard]] int GetBulletsPerShot() const;
		[[nodiscard]] float GetCooldown() const;
		[[nodiscard]] float GetSize() const;
	};

	WeaponStats operator+(WeaponStats stats, WeaponStats otherStats);
	EntityStats operator+(EntityStats stats, EntityStats otherStats);
	WeaponStats operator+=(WeaponStats stats, WeaponStats otherStats);
	EntityStats operator+=(EntityStats stats, EntityStats otherStats);
};