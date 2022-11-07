#pragma once
#include "projectile/Sparks.h"
#include "projectile/Tail.h"
#include "entity/Entity.h"

constexpr float TRAIL_COOLDOWN = 0.1f;

class Player final : public Entity
{
public:
	Player(Game& game, sf::Vector2f position);

protected:
	float _damage;

	std::vector<Tail> _trails;
	sf::Time _trailCooldown;

	float _sparksPerSecond;
	std::vector<Sparks> _sparks;
	sf::Time _sparksCooldown;
	float _sparksAngle;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Get trail position at the bottom of the ship that change with the rotation
	sf::Vector2f getTrailPosition() const;

	// Add a sparks, at the bottom of the ship with the given angle
	void AddSparks(float angleDegree);
public:
	void Update(sf::Time elapsed) override;
	void Move() override;
};
