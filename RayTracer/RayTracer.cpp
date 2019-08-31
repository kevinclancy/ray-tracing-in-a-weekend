// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <regex>
#include <cfloat>
#include <cmath>
#include <memory>

#include "ray.h"
#include "vec3.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "random.h"

using namespace std;


vec3 color(const ray& r, shared_ptr<hitable> world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001f, FLT_MAX, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else {
            return vec3(0.f, 0.f, 0.f);
        }
    }
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5f * (unit_direction.y() + 1.0f);
        return (1.f - t) * vec3(1.f, 1.f, 1.f) + t * vec3(0.5f, 0.7f, 1.f);
    }
}

shared_ptr<hitable> random_scene() {
    vector<shared_ptr<hitable>> list;
    list.push_back(
        make_shared<sphere>(vec3(0.f, -1000.f, 0.f), 1000.f, make_shared<lambertian>(vec3(0.5f, 0.5f, 0.5f)))
    );
    for (int a = -11; a < 11; ++a) {
        for (int b = -11; b < 11; ++b) {
            float choose_mat = random();
            vec3 center(a + 0.9f * random(), 0.2f, b + 0.9f * random());
            if ((center - vec3(4.f, 0.2f, 0.f)).length() > 0.9f) {
                if (choose_mat < 0.8) { 
                    shared_ptr<material> m = make_shared<lambertian>(vec3(random() * random(), random() * random(), random() * random()));
                    list.push_back(
                        make_shared<sphere>(center, 0.2, m)
                    );
                }
                else if (choose_mat < 0.95) {
                    shared_ptr<material> m = make_shared<metal>(vec3(0.5f*(1.f + random()), 0.5f*(1.f + random()), 0.5f*(1.f + random())));
                    list.push_back(make_shared<sphere>(center, 0.2, m));
                } 
                else
                {
                    shared_ptr<material> m = make_shared<dielectric>(1.5f);
                    list.push_back(make_shared<sphere>(center, 0.2, m));
                }
            }
        }
    }

    list.push_back(
        make_shared<sphere>(vec3(0.f, 1.f, 0.f), 1.f, make_shared<dielectric>(1.5f))
    );
    list.push_back(
        make_shared<sphere>(vec3(-4.f, -1.f, 0.f), 1.f, make_shared<lambertian>(vec3(0.4f, 0.2f, 0.1f)))
    );
    list.push_back(
        make_shared<sphere>(vec3(4.f, 1.f, 0.f), 1.f, make_shared<metal>(vec3(0.7f, 0.6f, 0.5f)))
    );

    return make_shared<hitable_list>(list);
}

int main()
{
    ofstream out("out.ppm");
    int nx = 200;
    int ny = 100;
    int numSamples = 100;
    out << "P3" << endl << nx << " " << ny << endl << 255 << endl;
    shared_ptr<hitable> world = random_scene();
    vec3 lookfrom(10.f, 1.f, 2.f);
    vec3 lookat(0.f, 0.f, -1.f);
    float dist_to_focus = (lookfrom - lookat).length();
    float aperature = 0.1f;
    camera cam(
        lookfrom, 
        lookat, 
        vec3(0.f,1.f,0.f), 
        20.f, 
        float(nx)/float(ny),
        aperature,
        dist_to_focus
    );

    for (int row = ny - 1; row >= 0; --row) {
        for (int col = 0; col < nx; ++col) {
            vec3 clr(0.f, 0.f, 0.f);
            for (int s = 0; s < numSamples; ++s) {
                float u = float(col + random()) / float(nx);
                float v = float(row + random()) / float(ny);
                ray r = cam.get_ray(u, v);
                clr += color(r, world, 0);
            }
            clr /= float(numSamples);
            clr = vec3(sqrt(clr[0]), sqrt(clr[1]), sqrt(clr[2]));
            int ir = int(255.99 * clr[0]);
            int ig = int(255.99 * clr[1]);
            int ib = int(255.99 * clr[2]);

            out << ir << " " << ig << " " << ib << endl;
        }
    }
}


