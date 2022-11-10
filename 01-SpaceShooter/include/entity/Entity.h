#pragma once
#include "DrawableObject.h"
#include "module/Module.h"
#include "projectile/Projectile.h"
#include "weapon/Weapon.h"

class Game;

class Entity : public DrawableObject
{
public:
	Entity(Game& game, sf::Vector2f position, const sf::Texture& texture,
		float health, float maxHealth, Stats::EntityStats stats, 
		Group groupIndex
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
	std::vector<Module*> _modules;

	Game& _game;

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
	Group GetProjectileGroup() const;

	void TakeDamage(Projectile* projectile);
	void TakeDamage(Entity* entity);

	void ChargeWeapon();
	void StopChargingWeapon() const;

	void AddBonusStats(const Stats::EntityStats bonusStats);
	void AddBonusStats(const Stats::WeaponStats bonusStats) { _weaponStats += bonusStats; }

	Stats::EntityStats GetTotalStats() const { return _stats + _bonusStats; }
	Stats::WeaponStats GetWeaponStats() const { return _weaponStats; }

	void AddModule(Module* module);
};
