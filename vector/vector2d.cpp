#include "vector2d.h"

namespace {
constexpr float PI = 3.14159265;

float radians(double degrees)
{
    return degrees * PI / 180;
}
}

vector2d::vector2d(float x, double y)
    : _x(x)
    , _y(y)
{
}

vector2d
vector2d::operator+(const vector2d& v) const
{
    return vector2d(_x + v.get_x(),
        _y + v.get_y());
}

void vector2d::operator+=(const vector2d& v)
{
    _x = _x + v.get_x();
    _y = _y + v.get_y();
}

vector2d
vector2d::operator-(const vector2d& v) const
{
    return vector2d(_x - v.get_x(),
        _y - v.get_y());
}

bool vector2d::operator==(const vector2d& v) const
{
    return _x == v.get_x() && _y == v.get_y();
}

vector2d
    vector2d::operator*(float scalar) const
{
    return vector2d(_x * scalar, _y * scalar);
}

void vector2d::operator*=(float scalar)
{
    _x *= scalar;
    _y *= scalar;
}

float
vector2d::dot(const vector2d& v) const
{
    return (_x * v.get_x()) + (_y * v.get_y());
}

float
vector2d::cross(const vector2d& v) const
{
    return (_x * v.get_y()) - (v.get_x() * _y); 
}


float
vector2d::length() const
{
    return sqrt((_x * _x) + (_y * _y));
}

vector2d
vector2d::unit() const
{
    return vector2d(_x / this->length(),
        _y / this->length());
}

float
vector2d::angleRadians() const
{
    return std::atan2(this->unit().get_x(),
        this->unit().get_y());
}

float
vector2d::angleDegrees() const
{
    return (this->angleRadians() / M_PI) * 180.0;
}

void vector2d::rotate(float degrees)
{
    float x = _x;
    auto r = radians(degrees);
    x = (cos(r) * _x) - (sin(r) * _y);
    _y = (sin(r) * _x) + (cos(r) * _y);
    _x = x;
}

vector2d
vector2d::rotated(float degrees) const
{
    auto r = radians(degrees);
    float x = (cos(r) * _x) - (sin(r) * _y);
    float y = (sin(r) * _x) + (cos(r) * _y);
    return {x, y};
}

vector2d
vector2d::direction_to(const vector2d& v) const
{
    return (v - *this).unit();
}

float
vector2d::distance_to(const vector2d& v) const
{
    return (v - *this).length();
}

std::ostream&
operator<<(std::ostream& os, const vector2d& v)
{
    os << "{" << v._x << ", " << v._y << "}";
    return os;
}
