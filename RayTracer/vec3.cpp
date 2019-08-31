#include "vec3.h"

vec3 random_in_unit_sphere()
{
    vec3 p;
    do {
        p = 2.0 * vec3(random(), random(), random()) - vec3(1.f, 1.f, 1.f);
    } while (p.squared_length() >= 1.0);
    return p;
}

vec3 random_in_unit_disk()
{
    vec3 p;
    do {
        p = 2.0 * vec3(random(), random(), 0) - vec3(1.f, 1.f, 0.f);
    } while (p.squared_length() >= 1.0);
    return p;
}

vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2.f * dot(v, n) * n;
}

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted)
{
    vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.f - ni_over_nt * ni_over_nt * (1.f - dt * dt);
    if (discriminant > 0.f)
    {
        refracted = ni_over_nt * (uv - dt * n) - sqrt(discriminant) * n;
        return true;
    }
    else
        return false;
}