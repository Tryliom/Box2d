#pragma once
#include "gui/Gui.h"
#include "module/Module.h"

class UpgradeChoiceGui final : public Gui
{
public:
	explicit UpgradeChoiceGui(Game& game);

private:
	std::vector<Module*> _modules;

	static std::vector<Module*> getAllModules();
	static std::vector<Module*> getThreeRandomModules();
};
