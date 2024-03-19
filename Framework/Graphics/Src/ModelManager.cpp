#include "Precompiled.h"
#include "ModelManager.h"
#include "ModelIo.h"

using namespace BobEngine;
using namespace BobEngine::Graphics;

namespace
{
    std::unique_ptr<ModelManager> sModelManager;
}

void ModelManager::StaticInitialize()
{
    ASSERT(sModelManager == nullptr, "ModelManager: Is already initalized");
    sModelManager = std::make_unique<ModelManager>();
}

void ModelManager::StaticTerminate()
{
    sModelManager.reset();
}

ModelManager* ModelManager::Get()
{
    ASSERT(sModelManager != nullptr, "ModelManager: was not initialized");
    return sModelManager.get();
}

ModelId ModelManager::GetModelId(const std::filesystem::path& filePath)
{
    return std::filesystem::hash_value(filePath);
}

ModelId ModelManager::LoadModel(const std::filesystem::path& filePath)
{
    const ModelId modelId = GetModelId(filePath);
    auto [iter, success] = mInventory.insert({ modelId, nullptr });
    if (success)
    {
        auto& modelPtr = iter->second;
        modelPtr = std::make_unique<Model>();
        ModelIO::LoadModel(filePath, *modelPtr);
    }
    return modelId;
}

const Model* ModelManager::GetModel(ModelId id)
{
    auto model = mInventory.find(id);
    if (model != mInventory.end())
    {
        return model->second.get();
    }
    return nullptr;
}

