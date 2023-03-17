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
    virtual void OnCreateShape();
    struct Vertex
    {
        M::MMath::Vector3 position;
        M::Color color;
    };
    std::vector<Vertex> mVerticies;

    ID3D11Buffer* mVertexBuffer = nullptr;
    ID3D11VertexShader* mVertexShader = nullptr;
    ID3D11InputLayout* mInputLayout = nullptr;
    ID3D11PixelShader* mPixelShader = nullptr;

};


class Triangle :public GameState
{
public:
    virtual ~Triangle() = default;

protected:
    void OnCreateShape() override;
};

class Square :public GameState
{
public:
    virtual ~Square() = default;

protected:
    void OnCreateShape() override;
};

class Diamond :public GameState
{
public:
    virtual ~Diamond() = default;

protected:
    void OnCreateShape() override;
};