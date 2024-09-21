#pragma once
#include "GeneralMenu.h"

namespace SnakeGame
{
	enum class ActivateReactionMainMenu
	{
		None, 
		Play, 
		Records,
		Exit
	};

	class MainMenu : public GeneralMenu
	{
	public:
		MainMenu(Settings& currentSettings);
		virtual ~MainMenu() = default;
		ActivateReactionMainMenu GetReaction() const;
	private:
		MenuStyle subMenuStyle;
		std::unordered_map<MenuNodePtr, ActivateReactionMainMenu> activateReactions;
	};
}