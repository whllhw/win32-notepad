#include<iostream>
using namespace std;
int main1();
int main2();
int main3();
int main4() {
	int num = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (i == j) break;
			num = sqrt(i * 1100 + j * 11);
			if (i * 1100 + j * 11 == num*num) {
				cout << i * 1100 + j * 11;
			}
		}
	}
	system("pause");
	return 0;
}
int main() {
	main1();
	main3();
	main4();
	cin.clear();
	main2();
}