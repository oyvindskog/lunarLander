#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#include <cmath>
#include <iostream>
#include <math.h>

class vector2d {

public:
  vector2d(float x, double y);

  float get_x() const { return _x; };
  float get_y() const { return _y; };

  vector2d operator+(const vector2d &) const;

  vector2d operator-(const vector2d &) const;

  void operator+=(const vector2d &);

  bool operator==(const vector2d &) const;

  vector2d operator*(float scalar) const;

  void operator*=(float scalar);

  float dot(const vector2d &) const;

  float cross(const vector2d &) const;

  float length() const;

  vector2d unit() const;

  float angleRadians() const;

  float angleDegrees() const;

  void rotate(float degrees);

  vector2d rotated(float degrees) const;

  vector2d direction_to(const vector2d &) const;

  float distance_to(const vector2d &) const;

  friend std::ostream &operator<<(std::ostream &os, const vector2d &v);

private:
  float _x = 0;
  float _y = 0;
};

#endif
