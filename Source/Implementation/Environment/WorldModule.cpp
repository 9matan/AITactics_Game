#include "stdafx.h"
#include "Environment/WorldModule.h"

#include "Atomic/Atomic2D/TileMap2D.h"
#include "Atomic/Atomic2D/TileMap2D.h"
#include "Atomic/Atomic2D/TmxFile2D.h"
#include "Atomic/Graphics/Octree.h"
#include "Atomic/Resource/ResourceCache.h"
#include "Atomic/Scene/Scene.h"


using namespace Atomic;

CWorldModule::CWorldModule(Context* context)
    : IWorldModule(context)
    , m_isInitialized(false)
    , m_tiledMapNodeId(0)
{
}

TileMap2D* CWorldModule::GetTiledMap2D() const
{
    assert(m_scene.NotNull());
    if (auto node = m_scene->GetNode(m_tiledMapNodeId))
    {
        return node->GetComponent<TileMap2D>();
    }

    return nullptr;
}

Scene* CWorldModule::GetScene() const
{
    return m_scene.Get();
}

void CWorldModule::Initialize() 
{
    assert(!m_isInitialized);
    m_scene = Atomic::MakeUnique<Scene>(context_);
    m_scene->CreateComponent<Octree>();
    
    m_tiledMapNodeId = CreateTiledMap(m_scene.Get());
    m_isInitialized = true;
}

void CWorldModule::Shutdown()
{
    assert(m_isInitialized);
    auto scene = context_->GetSubsystem<Scene>();

    if (auto node = scene->GetNode(m_tiledMapNodeId))
    {
        scene->RemoveChild(node);
    }
}

unsigned int CWorldModule::CreateTiledMap(Node* root)
{
    auto tiledMapNode = root->CreateChild("TiledMap");
    auto cache = GetSubsystem<ResourceCache>();
    auto tmxFile = cache->GetResource<TmxFile2D>("Tilemaps/Level1.tmx");
    auto tiledMap = tiledMapNode->CreateComponent<TileMap2D>();
    tiledMap->SetTmxFile(tmxFile);
    auto mapInfo = tiledMap->GetInfo();
    tiledMapNode->SetPosition({-mapInfo.GetMapWidth() *0.5f, -mapInfo.GetMapHeight() * 0.5f, 0.0f});
    return tiledMapNode->GetID();
}
