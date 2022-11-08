#pragma once
#include "DrawableObject.h"
#include "projectile/Projectile.h"
#include "weapon/Weapon.h"

class Game;

class Entity : public DrawableObject
{
public:
	Entity(Game& game, sf::Vector2f position, const sf::Texture& texture,
		float health, float maxHealth, Stats::EntityStats stats, 
		Group groupIndex, Weapon* weapon = nullptr, float angle = 0.f
	);
private:
	Stats::EntityStats _stats;
	Stats::EntityStats _bonusStats;

protected:
	sf::RectangleShape _shape;

	float _health;
	float _maxHealth;

	Group _groupIndex;
	Weapon* _weapon;
	Stats::WeaponStats _weaponStats;

	Game& _game;

	//std::vector<std::pair<Projectile*, sf::Time>> _hitCooldown;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

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

	void AddBonusStats(const Stats::EntityStats bonusStats) const { _bonusStats += bonusStats; }
	void AddBonusStats(const Stats::WeaponStats bonusStats) const { _weaponStats += bonusStats; }

	Stats::EntityStats GetTotalStats() const { return _stats + _bonusStats; }
};
