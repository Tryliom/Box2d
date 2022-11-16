#pragma once
#include "gui/gui.h"

class WeaponChoiceGui final : public Gui
{
public:
	explicit WeaponChoiceGui(Game& game);

protected:
	void deselectAll();
};