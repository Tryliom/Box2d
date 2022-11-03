#pragma once
#include "BasicBall.h"

class BlackHole final : public BasicBall
{
public:
	BlackHole(b2Body* body, sf::Vector2f position);
};