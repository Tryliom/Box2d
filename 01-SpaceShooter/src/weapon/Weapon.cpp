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

	_chargeAnimation = nullptr;
}

void Weapon::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	if (_chargeAnimation != nullptr && _isCharging)
	{
		target.draw(*_chargeAnimation, states);
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
	if (!_isCharging)
	{
		_isCharging = true;
		_currentCooldown = getTotalStats().GetCooldown();

		const sf::Vector2f size = entity->GetShape().getSize();
		const sf::Vector2f position = entity->GetShape().getPosition();

		_chargeAnimation = new CircleAttackCharge(position, (size.x + size.y) / 2.f, getTotalStats().GetCooldown());
	}
}

void Weapon::StopCharging()
{
	if (_isCharging)
	{
		_isCharging = false;
		_currentCooldown = getTotalStats().GetCooldown();

		if (_chargeAnimation != nullptr)
		{
			_chargeAnimation->Stop();
		}
	}
}

void Weapon::Shoot(Entity* entity, const Group bulletGroup)
{
	StopCharging();

	AudioManager::GetInstance().PlaySound(Sound::WEAPON_SHOOT);

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

	if (_chargeAnimation != nullptr)
	{
		_chargeAnimation->Update(elapsed);
	}
}

void Weapon::UpdatePosition(const sf::Vector2f position)
{
	if (_chargeAnimation != nullptr)
	{
		_chargeAnimation->UpdatePosition(position);
	}
}
