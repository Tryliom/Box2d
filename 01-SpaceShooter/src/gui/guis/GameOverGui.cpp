#include "gui/guis/GameOverGui.h"

#include "Game.h"

GameOverGui::GameOverGui(Game& game) : Gui(game)
{
	_background.setFillColor(sf::Color(0, 0, 0, 150));

	auto playButton = Button(
		sf::Vector2f(Game::WIDTH / 2.f, Game::HEIGHT / 2.f),
		sf::Vector2f(400, 50),
		true
	);

	playButton.SetText({
		TextLine({CustomText{.Text = "Return to menu", .Style = sf::Text::Style::Bold, .Size = 24}})
	});

	playButton.SetOnClick([&]() {
		_game.SetState(GameState::MAIN_MENU);
	});

	_buttons.emplace_back(playButton);

	// Create texts
	auto title = Text(
		sf::Vector2f(Game::WIDTH / 2.f, 100.f),
		{
			TextLine({CustomText{.Text = "You have merged with the void", .Size = 40}}),
		},
		-1,
		true
	);

	_texts.emplace_back(title);
}
