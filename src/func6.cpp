#include<cmath>
using namespace std; 
double func6(double x, double y) {
	double r = sqrt(x*x + y*y);
	if (r == 0.0)
		return 1.0;
	return sin(r)/r;
}
