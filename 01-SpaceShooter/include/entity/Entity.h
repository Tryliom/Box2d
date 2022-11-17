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
		float maxHealth, Stats::EntityStats stats, 
		Group groupIndex
	);
private:
	Stats::EntityStats _stats;

protected:
	sf::RectangleShape _shape;

	float _health;
	float _maxHealth;
	bool _invincible = false;

	float _lastHealth{ 0.f };
	sf::Time _healthDifferenceTime{ sf::Time::Zero };

	Group _groupIndex;
	Weapon* _weapon;
	Stats::WeaponStats _weaponStats;
	Stats::EntityStats _bonusStats;
	std::list<Module*> _modules;

	Game& _game;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	float getDeltaAngle(float angle) const;
	void rotate(float angle) const;

	void updateHealthDifference();

	virtual void onDeath();

public:
	void Update(sf::Time elapsed) override;
	virtual void Move(sf::Time elapsed);

	sf::Vector2f GetPosition() const;
	void SetPosition(sf::Vector2f position);

	sf::RectangleShape GetShape() const { return _shape; }
	float GetHealthPercentage() const { return _health / _maxHealth; }
	bool IsDead() const;
	Game& GetGame() const { return _game; }
	Group GetProjectileGroup() const;

	void TakeDamage(Projectile* projectile);
	void TakeDamage(Entity* entity);

	void ChargeWeapon();
	void StopChargingWeapon() const;
	virtual sf::Vector2f GetWeaponPosition() const;

	void AddBonusStats(const Stats::EntityStats bonusStats);
	void AddBonusStats(const Stats::WeaponStats bonusStats);

	Stats::EntityStats GetTotalStats() const;
	Stats::WeaponStats GetWeaponStats() const;

	void AddModule(Module* module);

	void ChangeWeapon(Weapon* weapon);
};
