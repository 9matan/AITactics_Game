#pragma once

#include "Atomic/Container/Ptr.h"
#include "Interface/Environment/IWorldModule.h"

namespace Atomic
{
class Node;
}

class CWorldModule : public IWorldModule
{
public:
    CWorldModule(Atomic::Context* context);
    virtual Atomic::TileMap2D* GetTiledMap2D() const override;
    virtual Atomic::Scene* GetScene() const override;
    virtual void Initialize() override;
    virtual void Shutdown() override;

private:
    unsigned int m_tiledMapNodeId;
    Atomic::UniquePtr<Atomic::Scene> m_scene;
    bool m_isInitialized;

private:
    unsigned int CreateTiledMap(Atomic::Node* root);
};