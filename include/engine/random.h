#pragma once

#include <random>
#include <vector>

namespace rnd{

class rnd{
private:
    std::mt19937 m_random;
public:
    rnd(int seed){
        m_random.seed(seed);
    }

    const int GetInt(int,int);
    const float GetFloat(float,float);

    const int Choose(std::vector<int>);
    const float Choose(std::vector<float>);
};

//Global random number generator, if needed add more constant generators to decouple the seeds
}
extern rnd::rnd G_RAND; 
