#include "weapon/weapons/Canon.h"

#include <iostream>

#include "Game.h"
#include "animation/chargeAnimations/CircleAttackCharge.h"
#include "projectile/bullets/CanonBullet.h"

Canon::Canon() : Weapon(20.f, 50.f, 0.f, 1000.f, 1, 1.5f)
{
	
}

sf::Vector2f Canon::getFrontPosition(const Entity& entity) const
{
	const sf::Vector2f size = entity.GetShape().getSize();
	const sf::Vector2f position = entity.GetShape().getPosition();

	const float angle = entity.GetShape().getRotation() + 90.f;
	const float x = position.x - (size.x * 0.5f) * std::cos(Game::DegreeToRad(angle));
	const float y = position.y - (size.y * 0.5f) * std::sin(Game::DegreeToRad(angle));

	return { x, y };
}

void Canon::StartCharging(Entity entity)
{
	Weapon::StartCharging(entity);

	const sf::Vector2f size = entity.GetShape().getSize();

	_chargeAnimation = new CircleAttackCharge(entity.GetPosition(), (size.x + size.y) / 2.f, _cooldown);
}

void Canon::Shoot(Entity entity, const Group bulletGroup)
{
	Weapon::Shoot(entity, bulletGroup);

	const float angle = Game::RadToDegree(entity.GetBody()->GetAngle());
	const sf::Time lifeTime = sf::seconds(_range / _speed);
	const b2Vec2 velocity = Game::GetLinearVelocity(_speed, angle);

	_bullets.emplace_back(new CanonBullet(
		entity.GetGame().GetNewBody(), getFrontPosition(entity),
		angle, velocity, lifeTime,
		_damage, false, bulletGroup
	));
}