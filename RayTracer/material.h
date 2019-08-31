#pragma once

#include "ray.h"
#include "hitable.h"
#include "mathutils.h"

class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
public:
    lambertian(const vec3& a) : albedo{ a } {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;

    vec3 albedo;
};

class metal : public material {
public:
    metal(const vec3& a) : albedo{ a } {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;

    vec3 albedo;
};

class dielectric : public material
{
public:
    dielectric(float ri) : ref_idx(ri) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;

    float ref_idx;
};