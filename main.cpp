#include "camera.h"
#include "colour.h"
#include "hittableList.h"
#include "sphere.h"
#include "utility.h"
#include "vec3.h"
#include <memory>

int main() {
  hittable_list world;

  auto ground_material = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
  world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

  for (int i = -11; i < 11; ++i) {
    for (int j = -11; j < 11; ++j) {
      auto choose_mat = random_double();
      point3 center(i + .9 * random_double(), 0.2, j + 0.9 * random_double());

      if ((center - point3(4, 0.3, 0)).lenght() > 0.9) {
        shared_ptr<material> sphere_material;

        if (choose_mat < 0.8) {
          auto albedo = color::random() * color::random();
          sphere_material = make_shared<lambertian>(albedo);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        } else if (choose_mat < 0.95) {
          auto albedo = color::random(0.5, 1);
          sphere_material = make_shared<metal>(albedo);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        } else {
          sphere_material = make_shared<dielectric>(1.5);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  auto material1 = make_shared<dielectric>(1.5);
  world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

  auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
  world.add(make_shared<sphere>(point3(-4, 1, 0), 1, material2));

  auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5));
  world.add(make_shared<sphere>(point3(4, 1, 0), 1, material3));

  camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 1200;
  cam.samples_per_pixel = 500;
  cam.max_depth = 50;

  cam.vfov = 20;
  cam.lookfrom = point3(13, 2, 3);
  cam.lookat = point3(0, 0, 0);
  cam.vup = vec3(0, 1, 0);

  cam.defocus_angle = 0.6;
  cam.focus_dist = 10;

  cam.render(world);

  return 0;
}
