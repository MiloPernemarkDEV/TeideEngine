#pragma once

#include <ostream>
#include "core.h"

struct TEIDE_API Vect3
{
public:
	float x{}, y{}, z{};

	Vect3();

	Vect3(float x, float y, float z) ;

	Vect3 cross(const Vect3& other);

	float dot (const Vect3& other);

	Vect3 operator+(const Vect3& other) const;

	Vect3 operator-(const Vect3& other) const;

	Vect3 operator*(const Vect3& other) const;

	Vect3 operator/(const Vect3& other) const;
};

 TEIDE_API std::ostream& operator<<(std::ostream& out, const Vect3& v);


