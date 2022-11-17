#include "gui/guis/WeaponChoiceGui.h"

#include <array>

#include "factory/WeaponFactory.h"
#include "manager/EntityManager.h"

constexpr std::array WEAPONS = {
	WeaponType::MACHINE_GUN,
	WeaponType::SNIPER,
	WeaponType::CANON,
	WeaponType::SHOT_GUN
};

WeaponChoiceGui::WeaponChoiceGui(Game& game) : Gui(game)
{
	// Create texts
	auto title = Text(
		sf::Vector2f(Game::WIDTH / 2.f, 100.f),
		{
			TextLine({CustomText{.Text = "Choose a weapon", .Size = 30}})
		},
		-1,
		true
	);

	_texts.emplace_back(title);

	// Create 3 buttons for each weapon
	constexpr float buttonWidth = 300.f;
	constexpr float margin = 20.f;
	constexpr float totalButtonsWidth = static_cast<float>(WEAPONS.size()) * buttonWidth + (static_cast<float>(WEAPONS.size()) - 1.f) * margin;

	for (const WeaponType type : WEAPONS)
	{
		auto weaponButton = Button(
			sf::Vector2f(
				Game::WIDTH / 2.f - totalButtonsWidth / 2.f + static_cast<float>(type) * totalButtonsWidth / static_cast<float>(WEAPONS.size()) + buttonWidth / 2.f,
				Game::HEIGHT * 2.f / 3.f
			),
			sf::Vector2f(buttonWidth, 50),
			true
		);

		weaponButton.SetText({
			TextLine({CustomText{.Text = WeaponFactory::GetWeaponName(type), .Style = sf::Text::Style::Bold, .Size = 24}})
		});
		weaponButton.SetOnClick([this, type, &weaponButton]() {
			Player* player = EntityManager::GetInstance().GetPlayer();

			WeaponFactory::AssignWeapon(type, player);
			deselectAll();
			_buttons[static_cast<int>(type)].Toggle();
			player->ChargeWeapon();
			_buttons.back().Show();
		});

		_buttons.emplace_back(weaponButton);
	}

	auto startButton = Button(
		sf::Vector2f(Game::WIDTH / 2.f, Game::HEIGHT * 3.f / 4.f),
		sf::Vector2f(200.f, 50.f),
		true
	);

	startButton.SetText({
		TextLine({CustomText{.Text = "Start", .Style = sf::Text::Style::Bold, .Size = 24}})
	});

	startButton.SetOnClick([this]() {
		EntityManager::GetInstance().GetPlayer()->StopChargingWeapon();
		_game.SetState(GameState::PLAYING);
	});

	startButton.Disable();

	_buttons.emplace_back(startButton);
}

void WeaponChoiceGui::deselectAll()
{
	for (Button& button : _buttons)
	{
		button.Toggle(false);
	}
}
