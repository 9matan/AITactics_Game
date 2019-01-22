#pragma once

#include "Interface/IGameApp.h"

class CGameApp : public IGameApp
{
    ATOMIC_OBJECT(CGameApp, IGameApp)
public:
    CGameApp(Atomic::Context* context, Atomic::UniquePtr<IGameAppDI> injector);

    virtual void Setup() override;
    virtual void Start() override;
    virtual void Stop() override;

private:
    template<typename TSubsys, typename TInjector>
    void InitializeSubsystem(TInjector const& di);
    template<typename TSubsys>
    void ShutdownSubsystem();
};

template<typename T, typename TInjector>
void CGameApp::InitializeSubsystem(TInjector const& di)
{
    auto subsystem = di.create<T*>();

    subsystem->Initialize();
    context_->RegisterSubsystem(subsystem);
}

template<typename T>
void CGameApp::ShutdownSubsystem()
{
    auto subsystem = context_->GetSubsystem<T>();
    subsystem->Shutdown();
    context_->RemoveSubsystem<T>();
}