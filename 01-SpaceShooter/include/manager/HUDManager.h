#pragma once
#include <SFML/Graphics.hpp>

class HUDManager final : public sf::Drawable
{
private:
	HUDManager();

	sf::RectangleShape _healthBackgroundBar;
	sf::RectangleShape _healthBar;

	// A simple white line draw to the bottom of the window
	sf::RectangleShape _xpBar;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	HUDManager(const HUDManager&) = delete;
	HUDManager& operator=(const HUDManager&) = delete;

	static HUDManager& GetInstance()
	{
		static HUDManager instance;
		return instance;
	}

	void Update(sf::Time elapsed);
};