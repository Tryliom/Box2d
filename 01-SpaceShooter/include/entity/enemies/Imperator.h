#pragma once
#include "entity/Enemy.h"

class Imperator final : public Enemy
{
public:
	Imperator(Game& game, sf::Vector2f position, int level);

protected:
	std::vector<Weapon*> _weapons;
	size_t _currentWeaponIndex{ 0 };

	void Update(sf::Time elapsed) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void onEndCycle() override;
	void nextWeapon();
};
