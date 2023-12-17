#pragma once
#include "GameState.h"
#include "Button.h"

class SDLApplication;

class PauseState :
    public GameState
{
private:
    static const std::string s_pauseID;

public:
    PauseState(SDLApplication* app);
    void Render() const override;
    void Update() override;
    void HandleEvent(const SDL_Event& e) override;

    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override { return s_pauseID; }

private:
    void CreateButtons();
};

