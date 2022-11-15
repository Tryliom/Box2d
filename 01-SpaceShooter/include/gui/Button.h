#pragma once
#include <functional>
#include <SFML/Graphics.hpp>

#include "Text.h"

const sf::Time HOVER_TIME = sf::seconds(0.1f);

class Button : public sf::Drawable
{
public:
	Button(sf::Vector2f position, sf::Vector2f size, bool centered = false);

protected:
	sf::Vector2f _position;
	sf::RectangleShape _background;
	Text _text;

	sf::Color _backgroundColor;
	sf::Color _hoverBackgroundColor;

	bool _hover{ false };
	bool _centered{ false };

	sf::Time _hoverTime{ sf::Time::Zero };

	std::function<void()> _onClick;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	virtual void Update(sf::Time elapsed);
	virtual void OnClick();
	virtual void OnStartHover();
	virtual void OnEndHover();

	void SetText(const std::vector<TextLine>& texts);
	sf::FloatRect GetGlobalBounds() const;
	bool IsHover() const;
	void SetOnClick(const std::function<void()>& onClick);
};
