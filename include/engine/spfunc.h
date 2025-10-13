#pragma once

#include <functional>
#include <vector>
namespace spworks{
namespace spfunc{

class spfunc{
public:
    std::function<void(spfunc*)> internal_func;

    std::vector<void*> interface;

    spfunc(std::function<void(spfunc*)> func) : internal_func(func) {}
};

}

}
