#include <iostream>
#include <string>
using namespace std;

string &task(const char *ch) {
	string *str = new string();
	for (int i = 0; ch[i] != '\0'; i++) {
		if (ch[i]<'Z'&&ch[i]>'A') {
			str->push_back(ch[i] + 32);
		}
		else if (ch[i]<'z'&& ch[i]>'a') {
			str->push_back(ch[i] - 32);
		}
	}
	return *str;
}

int main2() {
	string tmp;
	cout << "输入要改变的字符串" << endl;
	cin.clear();
	getline(cin, tmp);
	const char *ch;
	if (tmp.empty()) {
		ch = "I come From Csu!";
	}
	else {
		ch = tmp.c_str();
	}
	cout << task(ch);
	system("pause");
	return 0;
}