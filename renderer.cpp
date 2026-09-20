#include "colour.h"
#include "ray.h"
#include "vec3.h"
#include <iostream>

color ray_color(const ray &r) {
  vec3 unit_dir = unit_vector(r.direction());
  auto a = .5 * (unit_dir.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(.5, .7, 1.0);
}

int main() {
  auto aspect_ratio = 16.0 / 9.0;
  int img_width = 400;

  int img_height = int(img_width / aspect_ratio);
  img_height = (img_height < 1) ? 1 : img_height;

  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  // we do not use aspect_ratio because it is the ideal aspect ratio, but the
  // real ratio may not be so, eg if the height is less than 1, we set it to 1
  // so it is possible for the true aspect ratio to be different from the ideal
  // one
  auto viewport_width = viewport_height * (double(img_width) / img_height);
  auto camera_center = point3(0, 0, 0);

  auto viewport_u = vec3(viewport_width, 0, 0);
  auto viewport_v = vec3(0, -viewport_height, 0);

  auto pixel_delta_u = viewport_u / img_width;
  auto pixel_delta_v = viewport_v / img_height;

  auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) -
                             viewport_u / 2 - viewport_v / 2;
  auto pixel00_loc = viewport_upper_left + .5 * (pixel_delta_u + pixel_delta_v);

  // printing out the configuration of the image described in the PPM file
  std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

  for (int j = 0; j < img_height; ++j) {
    std::clog << "\rScanlines remaining: " << (img_height - j) << ' '
              << std::flush;
    for (int i = 0; i < img_width; ++i) {
      auto pixel_center =
          pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
      auto ray_direction = pixel_center - camera_center;
      ray r(camera_center, ray_direction);

      color pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }

  std::clog << "\nDone.\n";

  return 0;
}
