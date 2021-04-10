// ccagd.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <exception>

struct Vector
{
	Vector(double x, double y, double z) : x(x), y(y), z(z)
	{
	}

	Vector operator*(double multiplier) const
	{
		return Vector(x * multiplier, y * multiplier, z * multiplier);
	}

	const double x, y, z;
};

struct Point
{
	Point(double x, double y, double z) : x(x), y(y),z(z)
	{
	}

	Point operator*(double multiplier) const
	{
		return Point(x * multiplier, y * multiplier, z * multiplier);
	}

	Point operator/(double divisor) const
	{
		if (divisor != 0)
		{
			return Point(x / divisor, y / divisor, z / divisor);
		}
		else
		{
			throw std::exception("division by 0");
		}
	}

	Point operator+(const Point & p)
	{
		return Point(x + p.x, y + p.y, z + p.z);
	}

	Point operator+(const Vector & v)
	{
		return Point(x + v.x, y + v.y, z + v.z);
	}

	Point operator-(const Point & p)
	{
		return Point(x - p.x, y - p.y, z - p.z);
	}

	Point operator-(const Vector & v)
	{
		return Point(x - v.x, y - v.y, z - v.z);
	}

	friend std::ostream &operator << (std::ostream &os, Point &p) 
	{
		os << '[' << p.x << ',' << p.y << ',' << p.z << "],";

		return os;
	}

	const double x, y, z;
};

struct Berstein
{
	double operator()(int n, int i, double t)
	{
		if (n == 0 && i == 0)
		{
			return 1;
		}
		else if (i > n || i < 0)
		{
			return 0;
		}

		return (1.0 - t) * this->operator()(n - 1, i, t) + t * this->operator()(n - 1, i - 1, t);
	}
};

struct HermiteInterpolationAffice
{
	HermiteInterpolationAffice() : a(0), b(1.0) {}
	HermiteInterpolationAffice(double a, double b) : a(a), b(b) {}

	double H3_0_a(double t)
	{
		return berstein(3, 0, t) + berstein(3, 1, t);
	}

	double H3_1_a(double t)
	{
		return berstein(3, 1, t) *  (1.0 / 3.0) * (b - a);
	}

	double H3_2_a(double t)
	{
		return berstein(3, 2, t) * (-1.0 / 3.0) * (b - a);
	}

	double H3_3_a(double t)
	{
		return berstein(3, 2, t) + berstein(3, 3, t);
	}

	Point getpoint(const Point &p0, const Point &p1, const Vector &m0, const Vector & m1, double t)
	{
		return p0 * H3_0_a(t) + m0 * H3_1_a(t) + m1 * H3_2_a(t) + p1 * H3_3_a(t);
	}
	
	Berstein berstein;
	const double a, b;
};

int main()
{
	try
	{
		Point points[4] = { Point(0, 0, 0), Point(2, 2, 0), Point(4, 8, 1), Point(8, -1, 0) };
		Vector	tangent_vectors[4] = { Vector(-1, -1, 0), Vector(0, 1, 1), Vector(1, 0, 1), Vector(1, 5, 1) };

		HermiteInterpolationAffice hia = HermiteInterpolationAffice(-1, 5.1);

		for (int c = 0; c < 4 - 1; c++)
		{
			for (double t = 0; t < 1.01; t += 0.01)
			{
				Point pt = hia.getpoint(points[c], points[c + 1], tangent_vectors[c], tangent_vectors[c + 1], t);

				std::cout << pt << std::endl;
			}
		}
	}
	catch (std::exception &e)
	{
		std::cout << "Exception " << e.what() << std::endl;
	}
}
