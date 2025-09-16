#include "../../include/engine/random.h"
#include <chrono>
#include <random>

const int rnd::rnd::GetInt(int min, int max){
    std::uniform_int_distribution<> dist(min,max);
    return dist(m_random);
}


const float rnd::rnd::GetFloat(float min, float max){
    std::uniform_real_distribution<> dist(min,max);
    return dist(m_random);
}

rnd::rnd G_RAND = rnd::rnd(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());


const int rnd::rnd::Choose(std::vector<int> input){
    return input[G_RAND.GetInt(0, input.size()-1)];
}


const float rnd::rnd::Choose(std::vector<float> input){
    return input[G_RAND.GetInt(0, input.size()-1)];
}
