#include "manager/HUDManager.h"

#include "Game.h"
#include "manager/EntityManager.h"

HUDManager::HUDManager()
{
	_healthBackgroundBar.setSize(sf::Vector2f(400.f, 8.f));
	_healthBackgroundBar.setFillColor(sf::Color(40, 40, 40));
	_healthBackgroundBar.setOrigin(_healthBackgroundBar.getSize() / 2.f);
	_healthBackgroundBar.setPosition({ Game::WIDTH / 2.f, Game::HEIGHT - 20.f });
	_healthBackgroundBar.setOutlineColor(sf::Color::White);
	_healthBackgroundBar.setOutlineThickness(0.5f);
}

void HUDManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_healthBackgroundBar);
	target.draw(_healthBar);
}

void HUDManager::Update(sf::Time elapsed)
{
	float healthPercentage = EntityManager::GetInstance().GetPlayer()->GetHealthPercentage();

	if (healthPercentage < 0.f)
	{
		healthPercentage = 0.f;
	}

	_healthBar.setSize(sf::Vector2f(_healthBackgroundBar.getSize().x * healthPercentage, _healthBackgroundBar.getSize().y));
	_healthBar.setOrigin(_healthBar.getSize() / 2.f);
	_healthBar.setPosition(_healthBackgroundBar.getPosition());
	_healthBar.setFillColor(sf::Color::Red);
}
