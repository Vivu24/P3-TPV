#pragma once
#include "GameObject.h"
#include "EventHandler.h"
#include "texture.h"
#include <functional>
#include <list>
#include "Vector2D.h"

using Callback = std::function<void(void)>;

class Button : public GameObject, public EventHandler
{
private:
    Texture* myTexture = nullptr;
    std::list<Callback> myCallbacks;
    Point2D<int> myPosition;

public:
    Button(GameState* state, Texture* tex, Point2D<int> pos);

    void Connect(Callback newCb);
    void Render() const override;
    void Update() override {}
    void Save(ostream& out) const override {}
    void HandleEvent(const SDL_Event& event) override;
};

