#include "gui/Button.h"

#include <iostream>

#include "Game.h"

TempColor::TempColor(sf::Color color)
{
	R = color.r;
	G = color.g;
	B = color.b;
	A = color.a;
}

TempColor::TempColor(int r, int g, int b, int a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

TempColor::operator sf::Color() const
{
	return { static_cast<sf::Uint8>(R), static_cast<sf::Uint8>(G), static_cast<sf::Uint8>(B), static_cast<sf::Uint8>(A) };
}

TempColor TempColor::operator+(const TempColor& other) const
{
	return {R + other.R, G + other.G, B + other.B, A + other.A};
}

TempColor TempColor::operator-(const TempColor& other) const
{
	return {R - other.R, G - other.G, B - other.B, A - other.A};
}

TempColor TempColor::operator*(float factor) const
{
	return { static_cast<int>(R * factor), static_cast<int>(G * factor), static_cast<int>(B * factor), static_cast<int>(A * factor) };
}

Button::Button(const sf::Vector2f position, const sf::Vector2f size, const bool centered)
{
	_position = position;
	_centered = centered;

	_backgroundColor = sf::Color(0, 0, 0, 55);
	_hoverBackgroundColor = sf::Color(0, 0, 0, 255);
	_borderColor = sf::Color::White;
	_hoverBorderColor = sf::Color::White;
	_selectedBorderColor = sf::Color::Yellow;
	_borderThickness = -1.f;
	_hoverBorderThickness = -2.f;

	_background.setFillColor(_backgroundColor);
	_background.setOutlineColor(_borderColor);
	_background.setOutlineThickness(_borderThickness);
	_background.setPosition(_position);
	_background.setSize(size);

	if (_centered)
	{
		_background.setOrigin(_background.getSize() / 2.0f);
	}
}

void Button::SetText(const std::vector<TextLine>& texts)
{
	_text = Text(_position, texts, _background.getSize().x, _centered);
}

sf::FloatRect Button::GetGlobalBounds() const
{
	return _background.getGlobalBounds();
}

bool Button::IsHover() const
{
	return _hover;
}

void Button::SetOnClick(const std::function<void()>& onClick)
{
	_onClick = onClick;
}

void Button::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(_background, states);
	target.draw(_text, states);
}

void Button::Update(const sf::Time elapsed)
{
	if (_hover)
	{
		_hoverTime += elapsed;

		if (_hoverTime >= HOVER_TIME)
		{
			_hoverTime = HOVER_TIME;
		}
	}
	else
	{
		_hoverTime -= elapsed;

		if (_hoverTime <= sf::Time::Zero)
		{
			_hoverTime = sf::Time::Zero;
		}
	}

	const float ratio = _hoverTime.asSeconds() / HOVER_TIME.asSeconds();

	const TempColor backgroundColor = TempColor(_backgroundColor) + (TempColor(_hoverBackgroundColor) - TempColor(_backgroundColor)) * ratio;
	const float borderThickness = _borderThickness + (_hoverBorderThickness - _borderThickness) * ratio;
	TempColor borderColor = TempColor(_borderColor) + (TempColor(_hoverBorderColor) - TempColor(_borderColor)) * ratio;

	if (_selected)
	{
		borderColor = TempColor(_selectedBorderColor);
	}

	_background.setFillColor(static_cast<sf::Color>(backgroundColor));
	_background.setOutlineThickness(borderThickness);
	_background.setOutlineColor(static_cast<sf::Color>(borderColor));
}

void Button::OnClick(Game& game)
{
	if (_onClick)
	{
		_onClick();

		sf::Cursor cursor;
		cursor.loadFromSystem(sf::Cursor::Arrow);
		game.GetWindow().setMouseCursor(cursor);
	}
}

void Button::OnStartHover(Game& game)
{
	_hover = true;
	sf::Cursor cursor;
	cursor.loadFromSystem(sf::Cursor::Hand);
	game.GetWindow().setMouseCursor(cursor);
}

void Button::OnEndHover(Game& game)
{
	_hover = false;
	sf::Cursor cursor;
	cursor.loadFromSystem(sf::Cursor::Arrow);
	game.GetWindow().setMouseCursor(cursor);
}