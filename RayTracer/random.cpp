#include "random.h"
#include <random>

using namespace std;

default_random_engine re;
uniform_real_distribution<float> zero_to_one(0,1);

float random()
{
    return zero_to_one(re);
}
