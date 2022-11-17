#pragma once
#include <SFML/System/Time.hpp>

#include "Group.h"
#include "Stats.h"
#include "animation/ChargeAnimation.h"
#include "projectile/Projectile.h"

class Entity;

class Weapon : public sf::Drawable
{
public:
	Weapon(Stats::WeaponStats stats, Entity* user);

private:
	Stats::WeaponStats _stats;
	Entity* _user;

protected:
	float _currentCooldown;
	bool _isCharging;

	ChargeAnimation* _chargeAnimation;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	[[nodiscard]] Stats::WeaponStats getTotalStats() const;
	[[nodiscard]] sf::Time getLifeTime() const;

	virtual void shootBullet(b2Body* body, const sf::Vector2f position, const float angle, const b2Vec2 velocity, const Group bulletGroup) = 0;
public:
	virtual void StartCharging(Entity* entity);
	virtual void StopCharging();

	[[nodiscard]] bool CanShoot() const { return _currentCooldown <= 0.f; }
	[[nodiscard]] float GetCooldown() const { return getTotalStats().GetCooldown(); }
	[[nodiscard]] bool IsCharging() const { return _isCharging; }

	// You need to override this method and shoot the bullets
	virtual void Shoot(Entity* entity, Group bulletGroup);
	virtual void Update(sf::Time elapsed);
	virtual void UpdatePosition(const Entity* entity);
};
