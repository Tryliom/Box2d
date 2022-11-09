#include "weapon/Weapon.h"

#include "entity/Entity.h"
#include "box2d/b2_world.h"

Weapon::Weapon(const Stats::WeaponStats stats, Stats::WeaponStats& userStats) : _userStats(userStats)
{
	_stats = stats;
	_currentCooldown = getTotalStats().GetCooldown();
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

sf::Time Weapon::getLifeTime() const
{
	const Stats::WeaponStats stats = getTotalStats();

	return sf::seconds(stats.GetRange() / stats.GetSpeed());
}

void Weapon::StartCharging(Entity* entity)
{
	_isCharging = true;
	_currentCooldown = getTotalStats().GetCooldown();
}

void Weapon::StopCharging()
{
	_isCharging = false;
	_currentCooldown = getTotalStats().GetCooldown();

	_chargeAnimation->Stop();
}

void Weapon::Shoot(Entity* entity, Group bulletGroup)
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
	_bullets.erase(std::remove_if(_bullets.begin(), _bullets.end(), [](const Projectile* bullet)
	{
		if (bullet->IsDead())
		{
			bullet->GetBody()->GetWorld()->DestroyBody(bullet->GetBody());

			return true;
		}

		return false;
	}), _bullets.end());
}

void Weapon::UpdatePosition(const sf::Vector2f position)
{
	_chargeAnimation->UpdatePosition(position);
}
