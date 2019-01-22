#pragma once

#include "Interface/di/IGameAppDI.h"

#include "boost/di.hpp"

namespace Atomic
{
class Context;
}

class CGameAppDI : public IGameAppDI
{
public:
    CGameAppDI(Atomic::Context* context);

    virtual CGameAppInjector MakeInjector() const override;

private:
    Atomic::Context* m_context;
};