#pragma once
#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Game.h"
#include "Text.h"

class Gui : public sf::Drawable
{
public:
	explicit Gui(Game& game);

protected:
	sf::RectangleShape _background;
	std::vector<Button> _buttons;
	std::vector<Text> _texts;

	Game& _game;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	virtual void Update(sf::Vector2f mousePosition, sf::Time elapsed);
	virtual void CheckInputs(sf::Event event);
};
