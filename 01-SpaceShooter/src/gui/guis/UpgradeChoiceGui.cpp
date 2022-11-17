#include "gui/guis/UpgradeChoiceGui.h"

#include <random>

#include "module/modules/SparksModule.h"
#include "Game.h"
#include "manager/EntityManager.h"

UpgradeChoiceGui::UpgradeChoiceGui(Game& game) : Gui(game)
{
	_modules = getThreeRandomModules();

	constexpr float width = 600.f;
	constexpr float margin = 20.f;
	const float totalWidth = static_cast<float>(_modules.size()) * width + (static_cast<float>(_modules.size()) - 1.f) * margin;
	float x = Game::WIDTH / 2.f - totalWidth / 2.f + width / 2.f;

	// Create buttons corresponding to the number of modules in the list
	for (Module* module : _modules)
	{
		constexpr float height = 400.f;

		auto button = Button(
			sf::Vector2f(x - width / 2.f, Game::HEIGHT / 2.f - height / 2.f),
			sf::Vector2f(width, height),
			false
		);

		button.SetText(module->GetDescription());

		button.SetOnClick([this, module, &button]() {
			Player* player = EntityManager::GetInstance().GetPlayer();
			player->AddModule(module);
			player->UseCredit();

			_game.SetState(GameState::PLAYING);

			if (player->HasCredits())
			{
				_game.SetState(GameState::UPGRADE_CHOICE);
			}
		});

		_buttons.emplace_back(button);

		x += width + margin;
	}

	auto title = Text(
		sf::Vector2f(Game::WIDTH / 2.f, 100.f),
		{
			TextLine({CustomText{.Text = "Choose an upgrade", .Size = 30}})
		},
		-1,
		true
	);

	_texts.emplace_back(title);

	auto credits = Text(
		sf::Vector2f(Game::WIDTH / 2.f, 200.f),
		{
			TextLine({CustomText{.Text = std::to_string(EntityManager::GetInstance().GetPlayer()->GetCredits()) + " upgrade available", .Size = 25}})
		},
		-1,
		true
	);

	_texts.emplace_back(credits);
}

std::vector<Module*> UpgradeChoiceGui::getAllModules()
{
	return {
		new EntitySpeedModule(),
		new EntitySpeedPercentModule(),
		new EntityHealthRegenerationPercentModule(),
		new EntityRotationSpeedModule(),
		new EntityCollisionDamageModule(),
		new EntityCollisionDamagePercentModule(),
		new EntityCollisionReductionDamageModule(),
		new EntityCollisionReductionDamagePercentModule(),
		new WeaponDamagePercentModule(),
		new WeaponSpeedModule(),
		new WeaponSpeedPercentModule(),
		new WeaponBulletsPerShotModule(),
		new WeaponBulletsPerShotPercentModule(),
		new WeaponCooldownReductionPercentModule(),
		new WeaponSizeModule(),
		new WeaponMultipleProjectileModule(),
		new WeaponSingleProjectileModule(),
		new EntityShipSizeUpModule(),
		new EntityShipSizeDownModule()
	};
}

std::vector<Module*> UpgradeChoiceGui::getThreeRandomModules()
{
	auto modules = getAllModules();
	std::random_device osSeed;
	const uint_least32_t seed = osSeed();

	std::mt19937 generator(seed);

	std::ranges::shuffle(modules, generator);
	modules.resize(3);

	return modules;
}