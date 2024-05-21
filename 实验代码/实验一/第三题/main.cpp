#include<iostream>
using namespace std;

const double x0 = 1; 
const double x1 = 2;
double y00 = 1;
double y11 = 9;
const double m0 = 4;
const double m1 = 12;

double h0(double x) {
	return(1 - 2 * (x - x0) / (x0 - x1)) * ((x - x1) / (x0 - x1)) * ((x - x1) / (x0 - x1));
}

double h1(double x) {
	return(1 + 2 * (x - x1) / (x0 - x1)) * ((x - x0) / (x1 - x0)) * ((x - x0) / (x1 - x0));
}

double H0(double x) {
	return (x - x0) * ((x - x1) / (x0 - x1)) * ((x - x1) / (x0 - x1));
}
double H1(double x) {
	return (x - x1) * ((x - x0) / (x1 - x0)) * ((x - x0) / (x1 - x0));
}

double p(double x) {
	return y00 * h0(x) + y11 * h1(x) + m0 * H0(x) + m1 * H1(x);
}

int main() {
	cout << p(1.65) << endl;
	return 0;
}