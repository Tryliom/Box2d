#pragma once
#include "module/Module.h"
#include "projectile/bullets/PenetrationBullet.h"

class SparksModule final : public Module
{
public:
	SparksModule();

protected:
	sf::Time _sparksCooldown;
	sf::Time _sparksCurrentCooldown;

	float _sparksPerSecond;
	float _sparksAngle;

	void updateData(Entity* entity) override;

	void addSparks(float angleDegree, Entity* entity) const;

public:
	void Initialize(Entity* entity) override;

	// Events
	void Update(sf::Time elapsed, Entity* entity) override;

	void OnEntityMove(Entity* entity) override;

	std::vector<TextLine> GetDescription() const override;
};
