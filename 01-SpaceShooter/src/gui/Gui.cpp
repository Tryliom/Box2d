#include "gui/Gui.h"
#include "Game.h"

Gui::Gui(Game& game) : _game(game)
{
	_background.setSize(sf::Vector2f(Game::WIDTH, Game::HEIGHT));
	_background.setFillColor(sf::Color(0, 0, 0, 50));
}

void Gui::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_background, states);

	for (auto& button : _buttons)
	{
		target.draw(button, states);
	}

	for (auto& text : _texts)
	{
		target.draw(text, states);
	}
}

void Gui::Update(Game& game, const sf::Time elapsed)
{
	const auto mousePosition = sf::Vector2f(sf::Mouse::getPosition(game.GetWindow()));

	for (auto& button : _buttons)
	{
		button.Update(elapsed);

		if (button.GetGlobalBounds().contains(mousePosition))
		{
			if (!button.IsHover())
			{
				button.OnStartHover(game);
			}
		}
		else
		{
			if (button.IsHover())
			{
				button.OnEndHover(game);
			}
		}
	}
}

void Gui::CheckInputs(const sf::Event event, Game& game)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			for (auto& button : _buttons)
			{
				if (button.IsHover())
				{
					button.OnClick(game);
					break;
				}
			}
		}
	}
}
