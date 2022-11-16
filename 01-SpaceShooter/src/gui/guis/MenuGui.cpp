#include "gui/guis/MenuGui.h"

#include "Game.h"

MenuGui::MenuGui(Game& game) : Gui(game)
{
	// Create buttons
	auto playButton = Button(
		sf::Vector2f(Game::WIDTH / 2.f, Game::HEIGHT * 3.f / 4.f), 
		sf::Vector2f(200, 50),
		true
	);

	playButton.SetText({
		TextLine({CustomText{ .Text = "PLAY", .Style = sf::Text::Style::Bold, .Size = 24}})
	});
	playButton.SetOnClick([&]() {
		_game.SetState(GameState::WEAPON_CHOICE);
	});

	_buttons.emplace_back(playButton);

	auto quitButton = Button(
		sf::Vector2f(Game::WIDTH / 2.f, Game::HEIGHT - 100.f),
		sf::Vector2f(200, 50),
		true
	);

	quitButton.SetText({
		TextLine({CustomText{.Text = "QUIT", .Style = sf::Text::Style::Bold, .Size = 24}})
	});
	quitButton.SetOnClick([&]() {
		_game.Exit();
	});

	_buttons.emplace_back(quitButton);

	// Create texts
	auto title = Text(
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
