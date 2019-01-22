#pragma once
#include "Atomic/Core/Object.h"

namespace Atomic
{
class TileMap2D;
class Scene;
}

class IWorldModule : public Atomic::Object
{
    ATOMIC_OBJECT(IWorldModule, Atomic::Object)
public:
    IWorldModule(Atomic::Context* context): Atomic::Object(context) {};

    virtual Atomic::TileMap2D* GetTiledMap2D() const = 0;
    virtual Atomic::Scene* GetScene() const = 0;
    virtual void Initialize() = 0;
    virtual void Shutdown() = 0;
};