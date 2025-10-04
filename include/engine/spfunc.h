#pragma once

#include <functional>
#include <vector>
namespace spworks{
namespace spfunc{

class spfunc{
    std::function<void(spfunc*)> internal_func;

public:
    std::function<void(void)> func = [this](){ internal_func(this); };
    
    std::vector<void*> interface;

    spfunc(std::function<void(spfunc*)> func) : internal_func(func) {}
};

}

}
