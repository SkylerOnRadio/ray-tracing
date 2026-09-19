#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

using color = vec3;

void write_color(std::ostream &out, const color &pixel_color) {
  auto red = pixel_color.x();
  auto green = pixel_color.y();
  auto blue = pixel_color.z();

  int rbyte = int(255.999 * red);
  int gbyte = int(255.999 * green);
  int bbyte = int(255.999 * blue);

  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif // !COLOR_H
