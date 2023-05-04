#pragma once

#include <M/Inc/M.h>

using namespace M;
using namespace M::Graphics;


class GameState : public  M::AppState
{
public:
    virtual ~GameState() = default;
    virtual void Initialize() override;
    virtual void Terminate() override;

    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void DebugUI() override;
protected:
    
    void ShowNormals();
   

    Camera mCamera;
    DirectionalLight mDirectionalLight;

    Mesh mSphere;
    RenderObject mEarthObject;
    StandardEffect mStandardEffect;
 


    bool mShowNormals = false;
};

