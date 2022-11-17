#pragma once
#include "DrawableObject.h"

class XpShard final : public DrawableObject
{
public:
	XpShard(b2Body* body, sf::Vector2f position, int xp);

	void Update(sf::Time elapsed) override;

protected:
	sf::Sprite _sprite;

	bool _pickedUp;
	int _xp;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	bool IsPickedUp() const;
	int GetXp() const;

	void Destroy();
};
