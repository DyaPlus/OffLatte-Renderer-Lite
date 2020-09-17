#include <iostream>
#include "ray.h"
#include "render_output.h"

double hit_sphere(const point3& center, const double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (-b - sqrt(discriminant)) / (2.0 * a); //First intersection of sphere and ray
    }
}

color ray_gradient_color(const ray& r) {
    vec3 sphere_o(0, 0, -1);
    auto t = hit_sphere(sphere_o, 0.5, r);
    if (t >= 0)
    {
        auto n = unit_vector(r.at(t) - sphere_o);
        //Normal Map Rendering
        return 0.5 * color(n.x + 1, n.y + 1, n.z + 1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {

    // Image

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length); // -Z is the front direction

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (double(image_width) - 1);
            auto v = double(j) / (double(image_height) - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin); // a point on the near clipping plane minus the origin for direction
            write_color(std::cout,ray_gradient_color(r));
        }
    }
    std::cerr << "\nDone.\n";

}