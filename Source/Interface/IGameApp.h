#pragma once

#include "Atomic/Container/Ptr.h"
#include "Atomic/Engine/Application.h"

class IGameAppDI;

namespace Atomic
{
class Context;
}

class IGameApp : public Atomic::Application
{
    ATOMIC_OBJECT(IGameApp, Atomic::Application)
public:
    IGameApp(Atomic::Context* context, Atomic::UniquePtr<IGameAppDI> injector) 
        : Atomic::Application(context)
        , m_injector(injector.Detach())
    {
    }

protected:
    Atomic::UniquePtr<IGameAppDI> m_injector;
};