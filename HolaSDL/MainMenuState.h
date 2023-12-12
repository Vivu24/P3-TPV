#pragma once
#include "GameState.h"
#include "Button.h"

class MainMenuState :
    public GameState
{
private:
    static const std::string s_menuID;

public:
    MainMenuState(PlayState* app) : GameState(app) {}
    void Render() const override;
    void Update() override;
    void HandleEvent(const SDL_Event&) override;
    void Save(ostream&) const override;
    void HasDied(GameList<GameObject, true>::anchor) override;

    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override { return s_menuID; }

private:
    void CreateButtons();
};

