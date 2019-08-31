#include <cmath>
#include "mathutils.h"

float schlick(float cosine, float ref_idx)
{
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1.f - r0) * pow((1 - cosine), 5);
}
