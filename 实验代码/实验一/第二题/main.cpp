#include<iostream>
using namespace std;

struct Point {
	double _x;
	double _y;
	Point() {}
	Point(double x, double y) {
		_x = x;
		_y = y;
	}
};

//ѡȡ��ֵ�ڵ�
Point* getPoint() {
	Point* node = new Point[4];	//�������
	node[0]._x = 0;
	node[0]._y = -7;
	node[1]._x = 1;
	node[1]._y = -4;
	node[2]._x = 2;
	node[2]._y = 5;
	node[3]._x = 3;
	node[3]._y = 26;
	return node;
}

const int num = 4;
Point* node = getPoint();		//�ڵ�����

//�������ղ�ֵ��
class Lagrange {
public:
	Lagrange() {}

	//�������պ����㷨
	double get_p(double x) {
		double p = 0;
		for (int i = 0; i < num; i++) {
			//���㵥��
			double temp = 1;
			for (int j = 0; j < num; j++) {
				if (i == j)continue;
				else {
					temp *= (x - node[j]._x) / (node[i]._x - node[j]._x);
				}
			}
			p += temp * node[i]._y;
		}
		return p;
	}
};


//ţ�ٲ�ֵ��
class Newton {
public:
	Newton() {}

	//ţ�ٲ�ֵ��

	double get_p(double x) {
		int cur_num = 4;
		double value[num];

		int index = 0;
		double  main_value[3];

		for (int i = 0; i < num; i++) {
			value[i] = node[i]._y;
		}

		int distance = 1;
		for (; cur_num > 1; cur_num--) {
			for (int i = 0; i < cur_num - 1; i++) {
				value[i]   = (value[i+1] - value[i]) / (node[i + distance]._x - node[i]._x);
			}
			main_value[index] = value[0];
			index++;
			distance++;
		}
		return  node[0]._y + main_value[0] * (x - node[0]._x) + main_value[1] * (x - node[0]._x) * (x - node[1]._x)
			+ main_value[2] * (x - node[0]._x) * (x - node[1]._x) * (x - node[2]._x) ;
	}
		
};

int main() {
	Lagrange lagrange;
	cout << lagrange.get_p(1.65) << endl;
	Newton newton;
	cout << newton.get_p(1.65) << endl;
	return 0;
}