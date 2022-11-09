#pragma once
#include "weapon/Weapon.h"

class Trail final : public sf::Drawable
{
public:
	Trail(sf::Vector2f position, float angle, Group group);

private:
	Group _group;
	sf::Sprite _sprite;
	sf::Time _lifeTime;
	sf::Time _currentLifeTime;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Update(sf::Time elapsed);

	bool IsDead() const { return _currentLifeTime >= _lifeTime; }
};

class Sniper final : public Weapon
{
public:
	explicit Sniper(Stats::WeaponStats& userStats);

protected:
	std::vector<Trail> _trails;

	void shootBullet(b2Body* body, const sf::Vector2f position, const float angle, const b2Vec2 velocity, const Group bulletGroup) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	void Update(sf::Time elapsed) override;
};