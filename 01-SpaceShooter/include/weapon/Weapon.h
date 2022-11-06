#pragma once
#include <box2d/b2_body.h>
#include <SFML/System/Time.hpp>

#include "Group.h"
#include "animation/ChargeAnimation.h"

class Weapon : public sf::Drawable
{
public:
	Weapon(float damage, float speed, float spread, float range, int bulletsPerShot, float cooldown);

protected:
	float _damage;
	float _speed;
	float _spread;
	float _range;
	int _bulletsPerShot;
	float _cooldown;
	float _currentCooldown;
	bool _isCharging;

	ChargeAnimation* _chargeAnimation;

	//std::vector<Bullet> _bullets;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	virtual void StartCharging(b2Body* user, sf::Vector2f size);
	virtual void StopCharging();

	bool CanShoot() const { return _currentCooldown <= 0.f; }

	// You need to override this method and shoot the bullets
	virtual void Shoot(b2Body* user, Group bulletGroup);
	virtual void Update(sf::Time elapsed);
	virtual void UpdatePosition(sf::Vector2f position);
};
