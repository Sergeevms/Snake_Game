#pragma once
#include "GeneralMenu.h"

namespace SnakeGame
{
	enum class ActivateReactionPauseMenu
	{
		None,
		Play,
		MainMenu
	};

	class PauseMenu : public GeneralMenu
	{
	public:
		PauseMenu(const Settings& currentSettings);
		virtual ~PauseMenu() = default;
		ActivateReactionPauseMenu GetReaction() const;
	private:
		MenuStyle subMenuStyle;
		std::unordered_map<MenuNodePtr, ActivateReactionPauseMenu> activateReactions;
	};
}

