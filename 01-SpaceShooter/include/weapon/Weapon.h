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
	Weapon(Stats::WeaponStats stats, Stats::WeaponStats& userStats);

private:
	Stats::WeaponStats _stats;
	Stats::WeaponStats& _userStats;

protected:
	float _currentCooldown;
	bool _isCharging;

	ChargeAnimation* _chargeAnimation;

	std::vector<Projectile*> _bullets;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	[[nodiscard]] Stats::WeaponStats getTotalStats() const { return _stats + _userStats; }
	[[nodiscard]] sf::Time getLifeTime() const;
	sf::Vector2f getFrontPosition(const Entity* entity) const;

	virtual void shootBullet(b2Body* body, const sf::Vector2f position, const float angle, const b2Vec2 velocity, const Group bulletGroup) = 0;
public:
	virtual void StartCharging(Entity* entity);
	virtual void StopCharging();

	[[nodiscard]] bool CanShoot() const { return _currentCooldown <= 0.f; }

	// You need to override this method and shoot the bullets
	virtual void Shoot(Entity* entity, Group bulletGroup);
	virtual void Update(sf::Time elapsed);
	virtual void UpdatePosition(sf::Vector2f position);
};
