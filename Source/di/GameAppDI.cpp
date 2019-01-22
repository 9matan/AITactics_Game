#include "stdafx.h"
#include "di/GameAppDI.h"

#include "Atomic/Core/Context.h"
#include "Interface/Environment/IWorldModule.h"
#include "Environment/WorldModule.h"

using namespace Atomic;

template<typename T>
struct CPointerWrapper
{
public:
    CPointerWrapper(T* pointer): m_pointer(pointer) {}

    operator T*() { return m_pointer; }

    T* m_pointer;
};

namespace di = boost::di;

using CContextWrapper = CPointerWrapper<Context>;

CGameAppDI::CGameAppDI(Context* context)
    : m_context(context)
{
}

CGameAppInjector CGameAppDI::MakeInjector() const
{
    return std::move(
        di::make_injector(
            di::bind<Context>().to([context = m_context](auto const& injector)
            {
                return context;
            }), // <- TROUBLE need to have a look at provider
            di::bind<IWorldModule>().to<CWorldModule>()
        ));
}
