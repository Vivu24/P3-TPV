#pragma once
#include "GameState.h"

class SDLApplication;

class PauseState :
    public GameState
{
private:
    static const std::string s_menuID;

public:
    PauseState(SDLApplication* app) : GameState(app) {}
    void Render() const override;
    void Update() override;
    void HandleEvent(const SDL_Event& e) override;

    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override { return s_menuID; }

private:
    void CreateButtons();
};

