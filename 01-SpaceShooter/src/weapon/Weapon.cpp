#include "weapon/Weapon.h"

#include "entity/Entity.h"
#include "Game.h"
#include "animation/chargeAnimations/CircleAttackCharge.h"

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

sf::Vector2f Weapon::getFrontPosition(const Entity* entity) const
{
	const sf::Vector2f size = entity->GetShape().getSize();
	const sf::Vector2f position = entity->GetShape().getPosition();

	const float angle = entity->GetShape().getRotation() + 90.f;
	const float x = position.x - (size.x * 0.5f) * std::cos(Game::DegreeToRad(angle));
	const float y = position.y - (size.y * 0.5f) * std::sin(Game::DegreeToRad(angle));

	return { x, y };
}

void Weapon::StartCharging(Entity* entity)
{
	_isCharging = true;
	_currentCooldown = getTotalStats().GetCooldown();

	const sf::Vector2f size = entity->GetShape().getSize();

	_chargeAnimation = new CircleAttackCharge(entity->GetPosition(), (size.x + size.y) / 2.f, getTotalStats().GetCooldown());
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

	const Stats::WeaponStats stats = getTotalStats();
	const float angle = Game::RadToDegree(entity->GetBody()->GetAngle());
	const sf::Time lifeTime = getLifeTime();
	const sf::Vector2f frontPosition = getFrontPosition(entity);
	const int bulletPerShot = stats.GetBulletsPerShot();
	const float spread = stats.GetSpread() / 2.f;

	for (int i = 0; i < bulletPerShot; i++)
	{
		float angleAfterSpread = angle - spread + (spread * 2.f * static_cast<float>(i) + spread) / static_cast<float>(bulletPerShot);

		if (bulletPerShot == 1)
		{
			angleAfterSpread = angle;
		}

		const b2Vec2 velocity = Game::GetLinearVelocity(stats.GetSpeed(), angleAfterSpread);

		shootBullet(entity->GetGame().GetNewBody(), frontPosition, angleAfterSpread, velocity, bulletGroup);
	}
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
