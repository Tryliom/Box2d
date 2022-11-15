#include "gui/Gui.h"

Gui::Gui(Game& game) : _game(game)
{
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

void Gui::Update(const sf::Vector2f mousePosition, const sf::Time elapsed)
{
	for (auto& button : _buttons)
	{
		button.Update(elapsed);

		if (button.GetGlobalBounds().contains(mousePosition))
		{
			if (!button.IsHover())
			{
				button.OnStartHover();
			}
		}
		else
		{
			if (button.IsHover())
			{
				button.OnEndHover();
			}
		}
	}
}

void Gui::CheckInputs(const sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			for (auto& button : _buttons)
			{
				if (button.IsHover())
				{
					button.OnClick();
					break;
				}
			}
		}
	}
}
