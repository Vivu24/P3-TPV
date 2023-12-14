#pragma once
#include "GameObject.h"
#include "EventHandler.h"
#include "texture.h"
#include <functional>
#include <list>

using Callback = std::function<void(void)>;

class Button : public GameObject, public EventHandler
{
private:
    Texture* myTexture = nullptr;
    std::list<Callback> myCallbacks;

public:
    Button(GameState* state, Texture* tex);

    void Connect(Callback newCb);
    void Render() const override;
    void Update() override {}
    void Save(ostream& out) const override {}
    void HandleEvent(const SDL_Event& event) override {}
};

