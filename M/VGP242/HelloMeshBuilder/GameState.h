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
    virtual void OnCreateMesh();

    struct Vertex
    {
        M::MMath::Vector3 position;
        M::Color color;
    };
    Camera mCamera;
    ConstantBuffer mConstantBuffer;
    MeshPC mCube;
    VertexShader mVertexShader;
    MeshBuffer mMeshBuffer;
    PixelShader mPixelShader;
    
    //ID3D11InputLayout* mInputLayout = nullptr;
};

class Cube :public GameState
{
public:
    virtual ~Cube() = default;

protected:
    void OnCreateMesh() override
    {
        mCube = MeshBuilder::CreateCubePC(2.0f, Colors::AliceBlue);
    }
};

class Rectangle :public GameState
{
public:
    virtual ~Rectangle() = default;

protected:
    void OnCreateMesh() override
    {
        mCube = MeshBuilder::CreateRectanglePC(2.0f, 1.0f, 2.0f);
    }
};

class Plane :public GameState
{
public:
    virtual ~Plane() = default;

protected:
    void OnCreateMesh() override
    {
        mCube = MeshBuilder::CreatePlanePC(4.0f, 2.0f, 1.0f);

    }
};

class Cylinder :public GameState
{
public:
    virtual ~Cylinder() = default;

protected:
    void OnCreateMesh() override
    {
        mCube = MeshBuilder::CreateCylinderPC(5.0f, 3.0f);

    }
};

class Sphere :public GameState
{
public:
    virtual ~Sphere() = default;

protected:
    void OnCreateMesh() override
    {
        mCube = MeshBuilder::CreateSpherePC(10.0f, 10.0f, 3.0f);

    }
};