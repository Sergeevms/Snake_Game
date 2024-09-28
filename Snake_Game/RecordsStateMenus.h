#pragma once
#include "GeneralMenu.h"
namespace SnakeGame
{
	class RecordsStateNameMenu : public GeneralMenu
	{
	public:
		RecordsStateNameMenu(const Settings& currentSettings);
		virtual ~RecordsStateNameMenu() = default;
	};

	class RecordsStateMenu : public GeneralMenu
	{
	public:
		RecordsStateMenu(const Settings& currentSettings);
		virtual ~RecordsStateMenu() = default;
	};
}

