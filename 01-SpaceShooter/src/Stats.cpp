#include "Stats.h"

namespace Stats
{
	float EntityStats::GetHealthRegeneration() const
	{
		return HealthRegeneration * (1.f + HealthRegenerationPercentage);
	}

	float EntityStats::GetSpeed() const
	{
		return Speed * (1.f + SpeedPercentage);
	}

	float EntityStats::GetMaxSpeed() const
	{
		return GetSpeed() * 1000.f;
	}

	float EntityStats::GetRotationSpeed() const
	{
		return RotationSpeed;
	}

	float EntityStats::GetCollisionDamage() const
	{
		return CollisionDamage * (1.f + CollisionDamagePercentage);
	}

	float EntityStats::GetCollisionReductionDamage() const
	{
		return CollisionReductionDamage * (1.f + CollisionReductionDamagePercentage);
	}

	float EntityStats::GetCollisionDamage(const float collisionDamage) const
	{
		float damage = (collisionDamage - CollisionReductionDamage) * (1.f - CollisionReductionDamagePercentage);

		if (damage < 0.f)
		{
			damage = 0.f;
		}

		return damage;
	}

	float EntityStats::GetSize() const
	{
		return Size;
	}

	float WeaponStats::GetDamage() const
	{
		return Damage * (1.f + DamagePercentage);
	}

	float WeaponStats::GetSpeed() const
	{
		return Speed * (1.f + SpeedPercentage);
	}

	float WeaponStats::GetSpread() const
	{
		return Spread;
	}

	float WeaponStats::GetRange() const
	{
		return Range;
	}

	int WeaponStats::GetBulletsPerShot() const
	{
		return static_cast<int>(BulletsPerShot * (1.f + BulletsPerShotPercentage));
	}

	float WeaponStats::GetCooldown() const
	{
		return (Cooldown - CooldownReduction) * (1.f - CooldownReductionPercentage);
	}

	float WeaponStats::GetSize() const
	{
		return Size;
	}

	WeaponStats operator+(const WeaponStats stats, const WeaponStats otherStats)
	{
		WeaponStats newStats;

		newStats.Damage = stats.Damage + otherStats.Damage;
		newStats.DamagePercentage = stats.DamagePercentage + otherStats.DamagePercentage;

		newStats.Speed = stats.Speed + otherStats.Speed;
		newStats.SpeedPercentage = stats.SpeedPercentage + otherStats.SpeedPercentage;

		newStats.Spread = stats.Spread + otherStats.Spread;

		newStats.Range = stats.Range + otherStats.Range;

		newStats.BulletsPerShot = stats.BulletsPerShot + otherStats.BulletsPerShot;
		newStats.BulletsPerShotPercentage = stats.BulletsPerShotPercentage + otherStats.BulletsPerShotPercentage;

		newStats.Cooldown = stats.Cooldown + otherStats.Cooldown;
		newStats.CooldownReduction = stats.CooldownReduction + otherStats.CooldownReduction;
		newStats.CooldownReductionPercentage = stats.CooldownReductionPercentage + otherStats.CooldownReductionPercentage;

		newStats.Size = stats.Size + otherStats.Size;

		return newStats;
	}

	EntityStats operator+(const EntityStats stats, const EntityStats otherStats)
	{
		EntityStats newStats;

		newStats.HealthRegeneration = stats.HealthRegeneration + otherStats.HealthRegeneration;
		newStats.HealthRegenerationPercentage = stats.HealthRegenerationPercentage + otherStats.HealthRegenerationPercentage;

		newStats.Speed = stats.Speed + otherStats.Speed;
		newStats.SpeedPercentage = stats.SpeedPercentage + otherStats.SpeedPercentage;

		newStats.RotationSpeed = stats.RotationSpeed + otherStats.RotationSpeed;

		newStats.CollisionDamage = stats.CollisionDamage + otherStats.CollisionDamage;
		newStats.CollisionDamagePercentage = stats.CollisionDamagePercentage + otherStats.CollisionDamagePercentage;

		newStats.CollisionReductionDamage = stats.CollisionReductionDamage + otherStats.CollisionReductionDamage;
		newStats.CollisionReductionDamagePercentage = stats.CollisionReductionDamagePercentage + otherStats.CollisionReductionDamagePercentage;

		newStats.Size = stats.Size + otherStats.Size;

		return newStats;
	}

	WeaponStats operator+=(WeaponStats stats, const WeaponStats otherStats)
	{
		stats = stats + otherStats;
		return stats;
	}

	EntityStats operator+=(EntityStats stats, const EntityStats otherStats)
	{
		stats = stats + otherStats;
		return stats;
	}
}
