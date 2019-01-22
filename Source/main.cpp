#include "stdafx.h"

#include "GameApp.h"
#include "di/GameAppDI.h"

int RunApplication()
{
    auto context = Atomic::MakeUnique<Atomic::Context>();
    auto di = Atomic::MakeUnique<CGameAppDI>(context.Get());
    auto application = Atomic::MakeUnique<CGameApp>(context.Get(), Atomic::Move(di));
    return application->Run();
}

ATOMIC_DEFINE_MAIN(RunApplication());