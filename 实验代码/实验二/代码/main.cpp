#include<iostream>
#include<cmath>
using namespace std;

struct Arrange {
	double max;
	double min;
	Arrange() {}
	Arrange(double min, double max) {
		this->min = min;
		this->max = max;
	}
}arrange(0, 1);

double f(double x) {
	double result;
	result = x * exp(x) / ((1 + x) * (1 + x));
	return result;
}

double FUHUA_Trapezoid_Formula(int n) {
	double result = 0;
	double h = (arrange.max - arrange.min) / n;
	double x = arrange.min + h;
	
	double T = f(arrange.min)+f(arrange.max);
	for (int i = 0; i < n - 1; i++) {
		T += 2 * f(x);
		x += h;
	}
	
	result = T * h / 2;
	return result;
}

double FUHUA_Simpson(int n) {
	double result = 0;
	double h = (arrange.max - arrange.min) / n;
	double x = arrange.min + h;

	double T = f(arrange.min) + f(arrange.max);
	for (int i = 0; i < n - 1; i++) {
		T += 2 * f(x);
		x += h;
	}

	x = arrange.min + h/2;
	for (int i = 0; i < n; i++) {
		T += 4 * f(x);
		x += h;
	}

	result = T * h / 6;
	return result;
}

double Romberg(int n) {
	double T[4];
	 T[0] = (f(arrange.max) + f(arrange.min)) / 2;
	double h;
	for (int i = 1; (1 << i) <= n; i++) {
		h = (arrange.max - arrange.min) / (1 << (i - 1));
		double x = arrange.min + h / 2;
		double G = 0;
		for (int j = 0; j < (1<<(i-1)) ; j++) {
			G += f(x);
			x += h;
		}
		T[i] = T[i - 1] / 2 + G * h / 2;
	}

	for (int j = 1; j < 4; j++) {
		for (int i = 0; i < 4-j; i++) {
			T[i] = T[i + 1] * (1 << (j * 2)) / ((1 << (j * 2)) - 1) - T[i] / ((1 << (j * 2)) - 1);
		}
	}

	return T[0];
}

void test01() {
	double limitation = 1e-5;
	int step = 2;

	//复化梯形公式
	double lvalue = FUHUA_Trapezoid_Formula(1);		//last_estimated_value
	double cvalue = FUHUA_Trapezoid_Formula(step);	//cur_estimated_value
	for (; fabs(lvalue - cvalue) > limitation;) {
		lvalue = cvalue;
		step *= 2;
		cvalue = FUHUA_Trapezoid_Formula(step);
	}
	cout << "复化梯形公式" << endl ;
	cout << "最终区间等分数: " << step << endl;
	cout.precision(10);
	cout << "满足要求的定积分近似值: " << cvalue << endl;
	cout << endl << "--------------------" << endl;
}

void test02() {
	double limitation = 1e-5;
	int step = 2;

	//复化Simpson公式
	double lvalue = FUHUA_Simpson(1);		//last_estimated_value
	double cvalue = FUHUA_Simpson(step);	//cur_estimated_value
	for (; fabs(lvalue - cvalue) > limitation;) {
		lvalue = cvalue;
		step *= 2;
		cvalue = FUHUA_Simpson(step);
	}
	cout << endl << "复化Simpson公式" << endl ;
	cout << "最终区间等分数: " << step << endl;
	cout.precision(10);
	cout << "满足要求的定积分近似值: " << cvalue << endl;
	cout << endl << "--------------------" << endl;
}

void test03() {

	//龙贝格算法
	int step = 8;
	double limitation = 1e-5;
	double cvalue = Romberg(step);	//cur_estimated_value

	cout << endl << "龙贝格算法" << endl;
	cout.precision(10);
	cout << "满足要求的定积分近似值: " << cvalue << endl;
	cout << endl << "--------------------" << endl;
}

int main() {

	test01();
	test02();
	test03();

	return 0;
}