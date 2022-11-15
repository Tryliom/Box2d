#include "gui/Button.h"

#include "Game.h"


Button::Button(const sf::Vector2f position, const sf::Vector2f size, const bool centered)
{
	_position = position;
	_centered = centered;

	_backgroundColor = sf::Color(0, 0, 0, 50);
	_hoverBackgroundColor = sf::Color(10, 10, 10, 255);

	_background.setFillColor(_backgroundColor);
	_background.setOutlineColor(sf::Color::White);
	_background.setOutlineThickness(-1.0f);
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
	sf::Color color = _backgroundColor;

	color.r += static_cast<sf::Uint8>((_hoverBackgroundColor.r - _backgroundColor.r) * ratio);
	color.g += static_cast<sf::Uint8>((_hoverBackgroundColor.g - _backgroundColor.g) * ratio);
	color.b += static_cast<sf::Uint8>((_hoverBackgroundColor.b - _backgroundColor.b) * ratio);
	color.a += static_cast<sf::Uint8>((_hoverBackgroundColor.a - _backgroundColor.a) * ratio);

	_background.setFillColor(color);
}

void Button::OnClick()
{
	if (_onClick)
	{
		_onClick();
	}
}

void Button::OnStartHover()
{
	_hover = true;
	_background.setFillColor(_hoverBackgroundColor);
}

void Button::OnEndHover()
{
	_hover = false;
	_background.setFillColor(_backgroundColor);
}