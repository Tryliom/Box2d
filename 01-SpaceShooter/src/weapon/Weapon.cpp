#include "weapon/Weapon.h"

#include "entity/Entity.h"

Weapon::Weapon(const float damage, const float speed, const float spread, const float range, const int bulletsPerShot, const float cooldown)
{
	_damage = damage;
	_speed = speed;
	_spread = spread;
	_range = range;
	_bulletsPerShot = bulletsPerShot;
	_cooldown = cooldown;
	_currentCooldown = cooldown;
	_isCharging = false;

	_chargeAnimation = new ChargeAnimation();
}

void Weapon::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(*_chargeAnimation, states);

	for (const Projectile* bullet : _bullets)
	{
		target.draw(*bullet, states);
	}
}

void Weapon::StartCharging(Entity entity)
{
	_isCharging = true;
	_currentCooldown = _cooldown;
}

void Weapon::StopCharging()
{
	_isCharging = false;
	_currentCooldown = _cooldown;

	_chargeAnimation->Stop();
}

void Weapon::Shoot(Entity entity, Group bulletGroup)
{
	StopCharging();
}

void Weapon::Update(const sf::Time elapsed)
{
	if (_currentCooldown > 0.f && _isCharging)
	{
		_currentCooldown -= elapsed.asSeconds();
	}

	_chargeAnimation->Update(elapsed);

	for (Projectile* bullet : _bullets)
	{
		bullet->Update(elapsed);
	}

	// Remove bullets that have finished their life time
	_bullets.erase(std::remove_if(_bullets.begin(), _bullets.end(), [](const Projectile* bullet) { return bullet->IsDead(); }), _bullets.end());
}

void Weapon::UpdatePosition(const sf::Vector2f position)
{
	_chargeAnimation->UpdatePosition(position);
}
