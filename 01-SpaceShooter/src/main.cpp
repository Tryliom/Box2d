#include "Game.h"
#include "Assets.h"
#include "Stats.h"

int main()
{
	Assets::GetInstance();
	Game game;

	return game.Loop();
}