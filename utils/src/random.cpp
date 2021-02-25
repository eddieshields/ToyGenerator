#include "random.h"

int                                       Random::_seed        = 137;
std::map<std::thread::id,std::mt19937_64> Random::_engines     = std::map<std::thread::id,std::mt19937_64>();
std::mt19937_64                           Random::_engine      = std::mt19937_64();

std::uniform_real_distribution< real_t >  Random::_uniform     = std::uniform_real_distribution< real_t >();
std::exponential_distribution < real_t >  Random::_exponential = std::exponential_distribution < real_t >();
std::normal_distribution      < real_t >  Random::_normal      = std::normal_distribution      < real_t >();
std::uniform_int_distribution < int >     Random::_integer     = std::uniform_int_distribution < int >   (0,1);