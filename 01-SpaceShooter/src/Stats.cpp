#include "Stats.h"

#include "Game.h"

namespace Stats
{
	float EntityStats::GetHealthRegeneration() const
	{
		return HealthRegeneration * (1.f + HealthRegenerationPercentage);
	}

	float EntityStats::GetSpeed() const
	{
		return Speed * (1.f + SpeedPercentage) / Game::SCALE;
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

	TextLine GetTextLine(float value, std::string name, const bool isPercentage)
	{
		std::string prefix;

		if (value > 0.f)
		{
			prefix = "+";
		}

		name = " " + name;

		if (isPercentage)
		{
			value *= 100.f;

			name = "%" + name;
		}

		return TextLine({
			CustomText{.Text = prefix, .Size = 16},
			CustomText{.Text = std::to_string(static_cast<int>(value)), .Color = sf::Color::Yellow, .Size = 16},
			CustomText{.Text = name, .Size = 16}
		});
	}

	TextLine GetTextLine(const int value, const std::string& name, const bool isPercentage)
	{
		return GetTextLine(static_cast<float>(value), name, false);
	}

	std::vector<TextLine> EntityStats::GetTextLines() const
	{
		std::vector<TextLine> textLines;

		if (HealthRegeneration != 0.f)
		{
			textLines.push_back(GetTextLine(HealthRegeneration, "Health Regeneration", false));
		}

		if (HealthRegenerationPercentage != 0.f)
		{
			textLines.push_back(GetTextLine(HealthRegenerationPercentage, "Health Regeneration", true));
		}

		if (Speed != 0.f)
		{
			textLines.push_back(GetTextLine(Speed, "Ship speed", false));
		}

		if (SpeedPercentage != 0.f)
		{
			textLines.push_back(GetTextLine(SpeedPercentage, "Ship speed", true));
		}

		if (RotationSpeed != 0.f)
		{
			textLines.push_back(GetTextLine(RotationSpeed, "Rotation speed", false));
		}

		if (CollisionDamage != 0.f)
		{
			textLines.push_back(GetTextLine(CollisionDamage, "Collision damage", false));
		}

		if (CollisionDamagePercentage != 0.f)
		{
			textLines.push_back(GetTextLine(CollisionDamagePercentage, "Collision damage", true));
		}

		if (CollisionReductionDamage != 0.f)
		{
			textLines.push_back(GetTextLine(CollisionReductionDamage, "Collision reduction damage", false));
		}

		if (CollisionReductionDamagePercentage != 0.f)
		{
			textLines.push_back(GetTextLine(CollisionReductionDamagePercentage, "Collision reduction damage", true));
		}

		if (Size != 0.f)
		{
			textLines.push_back(GetTextLine(Size, "Ship size", true));
		}

		return textLines;
	}

	float WeaponStats::GetDamage() const
	{
		return Damage * (1.f + DamagePercentage);
	}

	float WeaponStats::GetSpeed() const
	{
		return Speed * (1.f + SpeedPercentage) / Game::SCALE;
	}

	float WeaponStats::GetSpread() const
	{
		return Spread;
	}

	float WeaponStats::GetRange() const
	{
		return Range / Game::SCALE;
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

	std::vector<TextLine> WeaponStats::GetTextLines() const
	{
		std::vector<TextLine> textLines;

		if (Damage != 0.f)
		{
			textLines.push_back(GetTextLine(Damage, "Bullet damage", false));
		}

		if (DamagePercentage != 0.f)
		{
			textLines.push_back(GetTextLine(DamagePercentage, "Bullet damage", true));
		}

		if (Speed != 0.f)
		{
			textLines.push_back(GetTextLine(Speed, "Bullet speed", false));
		}

		if (SpeedPercentage != 0.f)
		{
			textLines.push_back(GetTextLine(SpeedPercentage, "Bullet speed", true));
		}

		if (Spread != 0.f)
		{
			textLines.push_back(GetTextLine(Spread, "Weapon spread", false));
		}

		if (Range != 0.f)
		{
			textLines.push_back(GetTextLine(Range, "Weapon range", false));
		}

		if (BulletsPerShot != 0.f)
		{
			textLines.push_back(GetTextLine(BulletsPerShot, "Bullets per shot", false));
		}

		if (BulletsPerShotPercentage != 0.f)
		{
			textLines.push_back(GetTextLine(BulletsPerShotPercentage, "Bullets per shot", true));
		}

		if (Cooldown != 0.f)
		{
			textLines.push_back(GetTextLine(Cooldown, "Weapon cooldown", false));
		}

		if (CooldownReduction != 0.f)
		{
			textLines.push_back(GetTextLine(CooldownReduction, "Weapon cooldown reduction", true));
		}

		if (CooldownReductionPercentage != 0.f)
		{
			textLines.push_back(GetTextLine(CooldownReductionPercentage, "Weapon cooldown reduction", true));
		}

		if (Size != 0.f)
		{
			textLines.push_back(GetTextLine(Size, "Bullet size", true));
		}

		return textLines;
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

	WeaponStats operator+=(WeaponStats& stats, const WeaponStats otherStats)
	{
		stats = stats + otherStats;
		return stats;
	}

	EntityStats operator+=(EntityStats& stats, const EntityStats otherStats)
	{
		stats = stats + otherStats;
		return stats;
	}
}
