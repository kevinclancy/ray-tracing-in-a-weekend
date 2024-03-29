#pragma once

#include "ray.h"
#include <memory>

class material;

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
    std::shared_ptr<material> mat_ptr;
};

class hitable {
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

