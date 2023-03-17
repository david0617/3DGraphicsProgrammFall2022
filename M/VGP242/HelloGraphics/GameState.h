#pragma once

#include <M/Inc/M.h>

using namespace M;
using namespace M::Graphics;


class GameState : public  M::AppState
{
public:
    virtual ~GameState() = default;
    virtual void Initialize() override;

    virtual void Update(float deltaTime) override;
};