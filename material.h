#ifndef MATERIAL_H
#define MATERIAL_H

#include "colour.h"
#include "hittable.h"
#include "vec3.h"
#include <cmath>
class material {
public:
  virtual ~material() = default;

  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       color &attenuation, ray &scattered) const {
    return false;
  }
};

class lambertian : public material {
public:
  lambertian(const color &albedo) : albedo(albedo) {}

  // TODO: implement it scatttering sometimes with probability 1 - R
  // implement a mix of both where it scatters with some filed proability and
  // has attenuation albedo
  bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
               ray &scattered) const override {
    auto scatter_direction = rec.normal + random_unit_vector();

    if (scatter_direction.near_zero())
      scatter_direction = rec.normal;
    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }

private:
  color albedo;
};

class metal : public material {
public:
  metal(const color &albedo) : albedo(albedo) {}
  bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
               ray &scattered) const override {
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return true;
  };

private:
  color albedo;
};

class dielectric : public material {
public:
  dielectric(double refraction_index) : refraction_index(refraction_index) {}

  bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
               ray &scattered) const override {
    attenuation = color(1.0, 1.0, 1.0);
    double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

    vec3 unit_dir = unit_vector(r_in.direction());
    double cos_theta = std::fmin(dot(-unit_dir, rec.normal), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;
    vec3 dir;

    if (cannot_refract) {
      dir = reflect(unit_dir, rec.normal);
    } else {
      dir = refract(unit_dir, rec.normal, ri);
    }

    scattered = ray(rec.p, dir);
    return true;
  }

private:
  double refraction_index;

  static double reflectance(double cosine, double refraction_index) {
    auto r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
  }
};

#endif // !MATERAIL_H
