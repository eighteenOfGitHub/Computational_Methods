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

struct Range {
	double _max;
	double _min;
	Range() {}
	Range(double x, double y) {
		_max = x;
		_min = y;
	}
};

Range range(-5, 5);		//��Χ
int num = 11;			//�ڵ�����

//��Ŀ����
double f(double x) {
	double result = 1 / (1 + x * x);
	return result;
}
//ѡȡ��ֵ�ڵ�
Point* getPoint(Range range, int num) {
	Point* node = new Point[num];	//�������
	double node_x = range._max;
	double distance = (range._max - range._min) / (num - 1);
	for (int i = 0; i < num; i++) {
		double node_y = f(node_x);
		Point point(node_x, node_y);
		node[i] = point;
		node_x -= distance;
	}
	
		////����
		//cout << "�Ⱦ��ֵ�ڵ㣺" << endl;
		//for (int i = 0; i < num; i++) {
		//	cout << i <<" (" << node[i]._x << ", " << node[i]._y << ")" << endl;
		//}
	
	return node;
}

Point* node = getPoint(range, num);		//�ڵ�����

//�������ղ�ֵ��ʽ
class Lagrange{
public :
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
			p += temp*node[i]._y;
		}
		return p;
	}
};

//�ֶβ�ֵ��
class FenDuan {
public:
	FenDuan() {}

	//�ֶβ�ֵ�������㷨
	double get_p(double x) {
		double p = 0;
		int i = 0;
		for (; i < num; i++) {
			if (node[i]._x < x && node[i + 1]._x > x)
				break;
		}
		return  node[i]._y + (node[i + 1]._y - node[i]._y) / (node[i + 1]._x - node[i]._x) * (x - node[i]._x);
	}
};

int main() {
	double accurate_p1 = f(0.5);
	double accurate_p2 = f(4.5);
	
	Lagrange lagrange;
	double lagrange_p1 = lagrange.get_p(0.5);
	double lagrange_p2 = lagrange.get_p(4.5);
	FenDuan fenduan;
	double fenduan_p1 = fenduan.get_p(0.5);
	double fenduan_p2 = fenduan.get_p(4.5);
	cout << "X\ty(��ȷ)\t\ty(��������)\ty(�ֶ�����)\t���(��)\t���(��)" << endl;
	cout << "0.5\t" << accurate_p1 <<"\t\t" << lagrange_p1 << "\t" << fenduan_p1 << "\t\t"  << accurate_p1- lagrange_p1 <<"\t" << accurate_p1 - fenduan_p1 <<endl;
	cout << "4.5\t" << accurate_p2 << "\t" << lagrange_p2 << "\t\t" << fenduan_p2 << "\t"  << accurate_p2 - lagrange_p2<< "\t" << accurate_p2 - fenduan_p2 << endl;
	return 0;
}