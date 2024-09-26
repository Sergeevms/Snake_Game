#pragma once
#include "GeneralMenu.h"
namespace SnakeGame
{
	enum class ActivateReactionNameMenu
	{
		None,
		EnterName,
		Skip
	};

	class RecordsStateNameMenu : public GeneralMenu
	{
	public:
		RecordsStateNameMenu(const Settings& currentSettings);
		virtual ~RecordsStateNameMenu() = default;
		ActivateReactionNameMenu GetReaction() const;
	private:
		MenuStyle subMenuStyle;
		std::unordered_map<MenuNodePtr, ActivateReactionNameMenu> activateReactions;
	};

	enum class ActivateReactionRecordsMenu
	{
		None,
		Restart,
		ToMainMenu
	};

	class RecordsStateMenu : public GeneralMenu
	{
	public:
		RecordsStateMenu(const Settings& currentSettings);
		virtual ~RecordsStateMenu() = default;
		ActivateReactionRecordsMenu GetReaction() const;
	private:
		MenuStyle subMenuStyle;
		std::unordered_map<MenuNodePtr, ActivateReactionRecordsMenu> activateReactions;
	};
}

