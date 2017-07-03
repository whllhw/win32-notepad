#include<iostream>
#include <vector>
using namespace std;
int mid(vector<int> &a, int len) {
	float sum = 0;
	float arrange = 0;
	for (int i = 0; i < len; i++) {
		sum += a[i];
	}
	arrange = sum / len;
	std::cout << "平均数为；" << arrange << std::endl;
	int tmp1, closest, closeindex;
	closest = abs(a[0] - arrange);
	closeindex = 0;
	for (int i = 0; i < len; i++) {
		tmp1 = abs(a[i] - arrange);
		if (tmp1 < closest) {
			closest = tmp1;
			closeindex = i;
		}
	}
	return a[closeindex];
}

int main3() {
	vector<int> tmp;
	int buf;
	while(1)  {
		cin >> buf;
		if (!cin.eof()) {
			tmp.push_back(buf);
		}
		else {
			break;
		}
	} 
	
	//int a[] = { 1,3,3,2,5 };
	std::cout << "距离最近的为："<<mid(tmp,tmp.size());
	system("pause");
	return 0;
}