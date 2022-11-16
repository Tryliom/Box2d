#include "gui/guis/PauseGui.h"

#include "Game.h"

PauseGui::PauseGui(Game& game) : Gui(game)
{
	// Create buttons
	auto resumeButton = Button(
		sf::Vector2f(Game::WIDTH / 2.f, Game::HEIGHT * 3.f / 4.f),
		sf::Vector2f(200, 50),
		true
	);

	resumeButton.SetText({
		TextLine({CustomText{.Text = "Resume", .Style = sf::Text::Style::Bold, .Size = 24}})
	});
	resumeButton.SetOnClick([&]() {
		_game.SetState(GameState::PLAYING);
	});

	_buttons.emplace_back(resumeButton);

	auto quitButton = Button(
		sf::Vector2f(Game::WIDTH / 2.f, Game::HEIGHT - 100.f),
		sf::Vector2f(400, 50),
		true
	);

	quitButton.SetText({
		TextLine({CustomText{.Text = "Return to menu", .Style = sf::Text::Style::Bold, .Size = 24}})
	});
	quitButton.SetOnClick([&]() {
		_game.SetState(GameState::MAIN_MENU);
	});

	_buttons.emplace_back(quitButton);

	// Create texts
	auto title = Text(
		sf::Vector2f(Game::WIDTH / 2.f, 100.f),
		{
			TextLine({CustomText{.Text = "- Pause -", .Size = 40}})
		},
		-1,
		true
	);

	_texts.emplace_back(title);
}

void PauseGui::CheckInputs(sf::Event event, Game& game)
{
	Gui::CheckInputs(event, game);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		_game.SetState(GameState::PLAYING);
	}
}