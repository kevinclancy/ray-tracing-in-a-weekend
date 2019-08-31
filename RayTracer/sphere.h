#pragma once

#include <memory>
#include "hitable.h"

class sphere : public hitable {
public:
    sphere(std::shared_ptr<material> mat) : material{mat}, radius { 0.f }, center{ vec3(0.f,0.f,0.f) } {}
    sphere(vec3 cen, float r, std::shared_ptr<material> mat) : material{mat}, center { cen }, radius{ r } {}
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;

    ~sphere();

    std::shared_ptr<material> material;
    vec3 center;
    float radius;
};