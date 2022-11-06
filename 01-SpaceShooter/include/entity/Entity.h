#pragma once
#include "DrawableObject.h"
#include "animation/AttackCharge.h"

class Entity : public DrawableObject
{
public:
	Entity(b2Body* body, sf::Vector2f position, const sf::Texture& texture,
		float health, float maxHealth, float healthRegeneration, 
		float speed, float rotationSpeed, float maxSpeed, float angle = 0.f);

protected:
	sf::RectangleShape _shape;

	float _health;
	float _maxHealth;
	float _healthRegeneration;

	float _speed;
	float _maxSpeed;
	float _rotationSpeed;

	AttackCharge _attackCharge;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Returns the angle distance between this angle and the current angle
	float getDeltaAngle(float angle) const;
	void rotate(float angle) const;

public:
	void Update(sf::Time elapsed) override;
	virtual void Move();

	sf::Vector2f GetPosition() const;
	void SetPosition(sf::Vector2f position);

	float GetHealthPercentage() const { return _health / _maxHealth; }
	bool IsDead() const { return _health <= 0.f; }
	void TakeDamage(float damage);

	void StartAttackAnimation();
	void StopAttackAnimation();
};
