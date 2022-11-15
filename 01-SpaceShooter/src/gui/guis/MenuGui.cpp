#include "gui/guis/MenuGui.h"

#include "Game.h"

MenuGui::MenuGui(Game& game) : Gui(game)
{
	_background.setSize(sf::Vector2f(Game::WIDTH, Game::HEIGHT));
	_background.setFillColor(sf::Color(0, 0, 0, 100));

	// Create buttons
	Button playButton = Button(
		sf::Vector2f(Game::WIDTH / 2.f, Game::HEIGHT - 100.f), 
		sf::Vector2f(200, 50),
		true
	);

	playButton.SetText({
		TextLine({CustomText{ .Text = "PLAY", .Style = sf::Text::Style::Bold, .Size = 24}})
	});
	playButton.SetOnClick([&]() {
		_game.SetState(GameState::PLAYING);
	});

	_buttons.emplace_back(playButton);

	// Create texts
	Text title = Text(
		sf::Vector2f(Game::WIDTH / 2.f, 100.f),
		{
			TextLine({CustomText{.Text = "Space Shooter", .Size = 50}}),
			TextLine({CustomText{.Text = "A game by Tryliom", .Style = sf::Text::Style::Italic, .Size = 12}}),
		},
		-1,
		true
	);

	_texts.emplace_back(title);
}
