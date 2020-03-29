#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#include <cmath>
#include <iostream>
#include <math.h>

class vector2d {

public:
    vector2d(double x, double y);

    double get_x() const { return _x; };
    double get_y() const { return _y; };

    vector2d operator+(const vector2d&) const;

    vector2d operator-(const vector2d&) const;

    void operator+=(const vector2d&);

    bool operator==(const vector2d&) const;

    vector2d operator*(double scalar) const;

    void operator*=(double scalar);

    double dot(const vector2d&) const;

    double length() const;

    vector2d unit() const;

    double angleRadians() const;

    double angleDegrees() const;

    void rotate(double degrees);

    vector2d direction_to(const vector2d&) const;

    double distance_to(const vector2d&) const;

    friend std::ostream& operator<<(std::ostream& os, const vector2d& v);

private:
    double _x = 0;
    double _y = 0;
};

#endif
