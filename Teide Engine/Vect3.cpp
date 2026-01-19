#include "Vect3.h"

Vect3::Vect3(){}

Vect3::Vect3(float x, float y, float z) : x(x), y(y), z(z) {}

Vect3 Vect3::cross(const Vect3& other)
{
    return Vect3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

float Vect3::dot(const Vect3& other){
    return x * other.x + y * other.y + z * other.z;
}

Vect3 Vect3::operator+(const Vect3& other) const {
    return Vect3(x + other.x, y + other.y, z + other.z);
}

Vect3 Vect3::operator-(const Vect3& other) const {
    return Vect3(x - other.x, y - other.y, z - other.z);
}

Vect3 Vect3::operator*(const Vect3& other) const {
    return Vect3(x * other.x, y * other.y, z * other.z);
}

Vect3 Vect3::operator/(const Vect3& other) const {
    return Vect3(x / other.x, y / other.y, z / other.z);
}

TEIDE_API std::ostream& operator<<(std::ostream& out, const Vect3& v)
{
    out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return out;
}