#pragma once
#include <SFML/System/Time.hpp>

#include "Stats.h"
#include "projectile/Projectile.h"

class Entity;

class Module
{
public:
	explicit Module(Stats::EntityStats stats = {}, Stats::WeaponStats weaponStats = {});

protected:
	Stats::EntityStats _stats;
	Stats::WeaponStats _weaponStats;

	virtual void updateData(Entity* entity) {}

public:
	virtual void Initialize(Entity* entity) {}

	// Events
	virtual void Update(sf::Time elapsed, Entity* entity) {}

	virtual void OnEntityDeath(Entity* entity) {}
	virtual void OnEntityHit(Entity* entity, Projectile* projectile) {}
	virtual void OnEntityHit(Entity* entity, Entity* projectile) {}
	virtual void OnEntityCollision(Entity* entity) {}
	virtual void OnEntityMove(Entity* entity) {}

	// Getters
	[[nodiscard]] Stats::EntityStats GetStats() const { return _stats; }
	[[nodiscard]] Stats::WeaponStats GetWeaponStats() const { return _weaponStats; }

	[[nodiscard]] virtual std::vector<TextLine> GetDescription() const;
};

class EntitySpeedModule final : public Module
{
public:
	explicit EntitySpeedModule() : Module(
		Stats::EntityStats{
			.Speed = 100.f,
		}) {}
};

class EntitySpeedPercentModule final : public Module
{
public:
	explicit EntitySpeedPercentModule() : Module(
		Stats::EntityStats{
			.SpeedPercentage = 0.1f,
		}) {}
};

class EntityHealthRegenerationPercentModule final : public Module
{
public:
	explicit EntityHealthRegenerationPercentModule() : Module(
		Stats::EntityStats{
			.HealthRegenerationPercentage = 0.1f,
		}) {}
};

class EntityRotationSpeedModule final : public Module
{
public:
	explicit EntityRotationSpeedModule() : Module(
		Stats::EntityStats{
			.RotationSpeed = 5.f,
		}) {}
};

class EntityCollisionDamageModule final : public Module
{
public:
	explicit EntityCollisionDamageModule() : Module(
		Stats::EntityStats{
			.CollisionDamage = 10.f,
		}) {}
};

class EntityCollisionDamagePercentModule final : public Module
{
public:
	explicit EntityCollisionDamagePercentModule() : Module(
		Stats::EntityStats{
			.CollisionDamagePercentage = 0.1f,
		}) {}
};

class EntityCollisionReductionDamageModule final : public Module
{
public:
	explicit EntityCollisionReductionDamageModule() : Module(
		Stats::EntityStats{
			.CollisionReductionDamage = 10.f,
		}) {}
};

class EntityCollisionReductionDamagePercentModule final : public Module
{
public:
	explicit EntityCollisionReductionDamagePercentModule() : Module(
		Stats::EntityStats{
			.CollisionReductionDamagePercentage = 0.1f,
		}) {}
};

class WeaponDamageModule final : public Module
{
public:
	explicit WeaponDamageModule() : Module(
		{}, Stats::WeaponStats{
			.Damage = 10.f,
		}) {}
};

class WeaponDamagePercentModule final : public Module
{
public:
	explicit WeaponDamagePercentModule() : Module(
		{}, Stats::WeaponStats{
			.DamagePercentage = 0.1f,
		}) {}
};

class WeaponSpeedModule final : public Module
{
public:
	explicit WeaponSpeedModule() : Module(
		{}, Stats::WeaponStats{
			.Speed = 100.f,
		}) {}
};

class WeaponSpeedPercentModule final : public Module
{
public:
	explicit WeaponSpeedPercentModule() : Module(
		{}, Stats::WeaponStats{
			.SpeedPercentage = 0.1f,
		}) {}
};

class WeaponBulletsPerShotModule final : public Module
{
public:
	explicit WeaponBulletsPerShotModule() : Module(
		{}, Stats::WeaponStats{
			.BulletsPerShot = 1,
		}) {}
};

class WeaponBulletsPerShotPercentModule final : public Module
{
public:
	explicit WeaponBulletsPerShotPercentModule() : Module(
		{}, Stats::WeaponStats{
			.BulletsPerShotPercentage = 0.1f,
		}) {}
};

class WeaponCooldownReductionPercentModule final : public Module
{
public:
	explicit WeaponCooldownReductionPercentModule() : Module(
		{}, Stats::WeaponStats{
			.CooldownReductionPercentage = 0.1f,
		}) {}
};

class WeaponSizeModule final : public Module
{
public:
	explicit WeaponSizeModule() : Module(
		{}, Stats::WeaponStats{
			.Size = 0.5f,
		}) {}
};

class WeaponMultipleProjectileModule final : public Module
{
public:
	explicit WeaponMultipleProjectileModule() : Module(
		{}, Stats::WeaponStats{
			.DamagePercentage = -0.1f,
			.Spread = 10.f,
			.BulletsPerShot = 3,
			.BulletsPerShotPercentage = 1.f,
			.Size = -0.1f,
		}) {}
};

class WeaponSingleProjectileModule final : public Module
{
public:
	explicit WeaponSingleProjectileModule() : Module(
		{}, Stats::WeaponStats{
			.DamagePercentage = 0.5f,
			.Spread = -10.f,
			.Size = 0.3f,
		}) {}
};

class EntityShipSizeUpModule final : public Module
{
public:
	explicit EntityShipSizeUpModule() : Module(
		Stats::EntityStats{
			.HealthRegenerationPercentage = 1.f,
			.SpeedPercentage = -0.1f,
			.CollisionDamagePercentage = 0.3f,
			.CollisionReductionDamagePercentage = 0.1f,
			.Size = 0.3f,
		}) {}
};

class EntityShipSizeDownModule final : public Module
{
public:
	explicit EntityShipSizeDownModule() : Module(
		Stats::EntityStats{
			.SpeedPercentage = 0.2f,
			.RotationSpeed = 20.f,
			.CollisionDamagePercentage = -0.5f,
			.CollisionReductionDamagePercentage = -0.2f,
			.Size = -0.5f,
		}) {}
};