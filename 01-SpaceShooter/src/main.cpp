#include "Game.h"
#include "Assets.h"

int main()
{
	Assets::GetInstance();
	Game game;

	return game.Loop();
}