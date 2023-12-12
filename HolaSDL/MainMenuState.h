#pragma once
#include "GameState.h"
#include "Button.h"

class MainMenuState :
    public GameState
{
private:
    std::list<Button*> buttons;
    
    void Render() const override;
    void CreateButtons();
};

