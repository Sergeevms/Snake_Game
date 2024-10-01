#pragma once
#include "BaseInputHandler.h"
namespace SnakeGame
{
    class GeneralMenu;
    enum class MenuNodeActivateReaction;

    class BaseMenuInputHandler : public BaseInputHandler
    {
    public:
        BaseMenuInputHandler(GeneralMenu* currentMenu);
        virtual ~BaseMenuInputHandler() = default;
        virtual void SelectNext();
        virtual void SelectPrevious();
        virtual void ActivateCurrent();
        virtual void GoBack();
    protected:
        GeneralMenu* menu;
        std::unordered_map<MenuNodeActivateReaction, HandlerAction> activateMapping;
    };
}

