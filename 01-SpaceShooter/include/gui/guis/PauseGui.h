#pragma once
#include "gui/Gui.h"

class PauseGui final : public Gui
{
public:
	explicit PauseGui(Game& game);

protected:
	void CheckInputs(sf::Event event, Game& game) override;
};