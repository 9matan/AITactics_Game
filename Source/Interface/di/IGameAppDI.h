#pragma once

#include "Interface/di/IDependencyInjector.h"
#include "boost/di.hpp"

class IWorldModule;

using CGameAppInjector = boost::di::injector<
    IWorldModule*
>;

class IGameAppDI : public IDependencyInjector<CGameAppInjector> {};