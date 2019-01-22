#pragma once

template<typename TInjector>
class IDependencyInjector
{
public:
    virtual TInjector MakeInjector() const = 0;
};