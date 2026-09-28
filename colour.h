#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

#include <iostream>

using color = vec3;

void write_color(std::ostream &out, const color &pixel_color) {
  auto red = pixel_color.x();
  auto green = pixel_color.y();
  auto blue = pixel_color.z();

  static const interval intensity(0.000, 0.999);
  int rbyte = int(256 * intensity.clamp(red));
  int gbyte = int(256 * intensity.clamp(green));
  int bbyte = int(256 * intensity.clamp(blue));

  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif // !COLOR_H
