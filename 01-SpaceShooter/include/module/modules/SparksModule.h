#pragma once
#include "module/Module.h"
#include "projectile/bullets/Spark.h"

class SparksModule final : public Module
{
public:
	SparksModule();

protected:
	std::vector<Spark> _sparks;
	sf::Time _sparksCooldown;
	sf::Time _sparksCurrentCooldown;

	float _sparksPerSecond;
	float _sparksAngle;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateData(Entity* entity) override;

	void addSparks(float angleDegree, Entity* entity);

public:
	void Initialize(Entity* entity) override;

	// Events
	void Update(sf::Time elapsed, Entity* entity) override;

	void OnEntityMove(Entity* entity) override;
};
