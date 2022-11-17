#pragma once
#include "animation/Tail.h"
#include "entity/Entity.h"
#include "projectile/XpShard.h"

constexpr float TAIL_COOLDOWN = 0.1f;

class Player final : public Entity
{
public:
	explicit Player(Game& game);

protected:
	int _xp{ 0 };
	int _level{ 1 };
	int _credits{ 0 };

	std::list<Tail> _tails;
	sf::Time _tailCooldown;

	bool _copilot{ false };

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Get tail position at the bottom of the ship that change with the rotation
	sf::Vector2f getTailPosition() const;

	void onLevelUp();

public:
	void Update(sf::Time elapsed) override;
	void Move(sf::Time elapsed) override;

	void TakeControl();
	void ReleaseControl();
	bool IsAlive() const;
	bool IsCopilot() const;

	int GetMaxXp() const;
	float GetXpPercentage() const;

	bool HasCredits() const;
	void UseCredit();
	int GetCredits() const;

	void Contact(const XpShard* xpShard);

	void TryToShoot();
};
