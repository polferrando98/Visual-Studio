#include <iostream>
#include "Vec3.h"
using namespace std;

int main() {
	Vec3<int> v1;
	Vec3<int> v2(2,2,2);

	Vec3<int> result;

	v1.setCoords(1, 1, 1);

	v1 += v2;
	v1 = v2;

	v1.print();
	
	getchar();
	return 0;
}