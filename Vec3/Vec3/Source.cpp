#include <iostream>
#include "Vec3.h"
using namespace std;

int main() {
	Vec3<float> v1;
	Vec3<float> v2(2,2,2);

	Vec3<float> result;

	v1.setCoords(1, 1, 1);

	v1 += v2;

	cout << v1.distance_to(v2);
	
	getchar();
	return 0;
}