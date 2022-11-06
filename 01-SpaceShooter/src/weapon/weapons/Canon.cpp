#include "weapon/weapons/Canon.h"

#include "Game.h"
#include "animation/chargeAnimations/CircleAttackCharge.h"

Canon::Canon() : Weapon(20.f, 0.8f, 0.f, 100.f, 1, 1.5f)
{
	
}

void Canon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Weapon::draw(target, states);

	
}

void Canon::StartCharging(b2Body* user, const sf::Vector2f size)
{
	Weapon::StartCharging(user, size);

	_chargeAnimation = new CircleAttackCharge(Game::MeterToPixel(user->GetPosition()), (size.x + size.y) / 2.f, _cooldown);
}

void Canon::Shoot(b2Body* user, const Group bulletGroup)
{
	Weapon::Shoot(user, bulletGroup);
}