#pragma once
#include "DrawableObject.h"

class Sparks final : public DrawableObject
{
public:
	Sparks(b2Body* body, sf::Vector2f position, float angle, b2Vec2 velocity, float damagePerSeconds);

protected:
	sf::Sprite _sprite;

	sf::Time _lifeTime;
	sf::Time _currentLifeTime;

	float _damagePerSecond;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Update(sf::Time elapsed) override;

	bool IsDead() const { return _currentLifeTime >= _lifeTime; }

	float GetDamagePerSecond() const { return _damagePerSecond; }
};