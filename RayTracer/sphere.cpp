#include "sphere.h"

sphere::~sphere()
{
}

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.f * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant > 0.f) {
        float temp = (-b - sqrt(discriminant)) / (2.f * a);
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = material;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / (2.f * a);
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = material;
            return true;
        }
    }
    return false;
}
