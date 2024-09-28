#pragma once
#include "GeneralMenu.h"

namespace SnakeGame
{
	class PauseMenu : public GeneralMenu
	{
	public:
		PauseMenu(const Settings& currentSettings);
		virtual ~PauseMenu() = default;
	};
}

