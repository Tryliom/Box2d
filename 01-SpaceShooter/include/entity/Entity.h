#pragma once
#include "DrawableObject.h"
#include "projectile/Projectile.h"
#include "weapon/Weapon.h"

class Game;

class Entity : public DrawableObject
{
public:
	Entity(Game& game, sf::Vector2f position, const sf::Texture& texture,
		float health, float maxHealth, float healthRegeneration, 
		float speed, float rotationSpeed, float maxSpeed, Group groupIndex, Weapon* weapon = nullptr, float angle = 0.f);

protected:
	sf::RectangleShape _shape;

	float _health;
	float _maxHealth;
	float _healthRegeneration;

	float _speed;
	float _maxSpeed;
	float _rotationSpeed;

	Group _groupIndex;
	Weapon* _weapon;

	Game& _game;

	//std::vector<std::pair<Projectile*, sf::Time>> _hitCooldown;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Returns the angle distance between this angle and the current angle
	float getDeltaAngle(float angle) const;
	void rotate(float angle) const;

public:
	void Update(sf::Time elapsed) override;
	virtual void Move();

	sf::Vector2f GetPosition() const;
	void SetPosition(sf::Vector2f position);

	sf::RectangleShape GetShape() const { return _shape; }
	float GetHealthPercentage() const { return _health / _maxHealth; }
	bool IsDead() const { return _health <= 0.f; }
	Game& GetGame() const { return _game; }

	void TakeDamage(Projectile* projectile);

	void ChargeWeapon() const;
	void StopChargingWeapon() const;
};
