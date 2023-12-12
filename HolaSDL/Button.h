#pragma once
#include "GameObject.h"
#include "EventHandler.h"
#include "texture.h"
#include <functional>
#include <list>

using Callback = std::function<void(void)>;

class Button :
    public GameObject, public EventHandler
{
private:
    Texture* myTexture;
    list<Callback> myCallbacks;

public:
    Button(Texture* tex);

    void Connect(Callback newCb);
    void Render() const override;
    void Update() override;
    void Save(ostream&) const override;
    void HandleEvent(const SDL_Event&) override;
};

