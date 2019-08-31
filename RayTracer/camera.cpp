#include "camera.h"
#include "ray.h"
#include <cmath>

camera::camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist) {
    float pi = acos(-1.f);
    lens_radius = aperture / 2.f;
    float theta = (vfov * pi) / 180.f;
    float half_height = tan(theta / 2.f);
    float half_width = aspect * half_height;
    origin = lookfrom;
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);
    lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
    horizontal = 2.f * half_width * focus_dist * u;
    vertical = 2.f * half_height * focus_dist * v;
}

ray camera::get_ray(float s, float t)
{
    vec3 rd = lens_radius * random_in_unit_disk();
    vec3 offset = (rd.x() * u) + (rd.y() * v);
    return ray(
        origin + offset,
        lower_left_corner + s * horizontal + t * vertical - origin - offset
    );
}