// Chapter3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <chrono>

using namespace std::chrono;

extern "C" void PPMStart(int image_width, int image_height);
extern "C" void PPMAddPixel(int r, int g, int b);

struct point
{
	double	x;
	double	y;
	double	z;

	point(double x, double y, double z) : x(x), y(y), z(z) {}
	point() : x(0), y(0), z(0) {}

	point operator*(double d)
	{
		return point(x * d, y * d, z * d);
	}

	point operator+(point p)
	{
		return point(x + p.x, y + p.y, z + p.z);
	}
};

extern "C" int deCasteljau_(double t, struct point* b1, struct point* b2, struct point* outb);
extern "C" int factorial_(int n);

int deCasteljau(double t, struct point* b1, struct point* b2, struct point* outb);
int factorial(int n);

int main()
{
	struct point b1 = { 0,0,0 };
	struct point b2 = { 2,3,4 };
	struct point b3;

	auto start = high_resolution_clock::now();
	int ret = deCasteljau(0.42, &b1, &b2, &b3);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start);


	if (ret)
	{
		std::cout << b3.x << std::endl;
		std::cout << b3.y << std::endl;
		std::cout << b3.z << std::endl;
	}

	std::cout << "Time taken by first: "
		<< duration.count() << " nanoseconds" << std::endl;

	start = high_resolution_clock::now();
	ret = deCasteljau_(0.42, &b1, &b2, &b3);
	stop = high_resolution_clock::now();
	duration = duration_cast<nanoseconds>(stop - start);
	
	if (ret)
	{
		std::cout << b3.x << std::endl;
		std::cout << b3.y << std::endl;
		std::cout << b3.z << std::endl;
	}
	
	std::cout << "Time taken by second: "
		<< duration.count() << " nanoseconds" << std::endl;

	//factorial

	start = high_resolution_clock::now();
	ret = factorial(13);
	stop = high_resolution_clock::now();
	duration = duration_cast<nanoseconds>(stop - start);

	std::cout << ret  << std::endl;

	std::cout << "C factorial: "
		<< duration.count() << " nanoseconds" << std::endl;

	start = high_resolution_clock::now();
	ret = factorial_(13);
	stop = high_resolution_clock::now();
	duration = duration_cast<nanoseconds>(stop - start);

	std::cout << ret << std::endl;

	std::cout << "ASM factorial: "
		<< duration.count() << " nanoseconds" << std::endl;
}

int deCasteljau(double t, struct point* b1, struct point* b2, struct point* outb)
{
	*outb =   *b1 * (1.0 - t) + *b2 * t;

	return 1;
}

int factorial(int n)
{
	if (n == 1)
	{
		return n;
	}
	else
	{
		return factorial(n - 1) * n;
	}
}

void PPMStart(int image_width, int image_height)
{
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
}

void PPMAddPixel(int r, int g, int b)
{
	std::cout << r << ' ' << g << ' ' << b << '\n';
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
