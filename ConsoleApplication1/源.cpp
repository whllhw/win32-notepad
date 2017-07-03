#include <iostream>
#include <string>
using namespace std;
struct str{
	char ch;
	str *next;
};

void conncet(str &st1, str &st2) {
	str *p = &st1;
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = &st2;
}

str &create(const char *ch) {
	str *a = new str();
	str *p = a;
	for (int i = 0; ch[i] != '\0'; i++) {
		p->ch = ch[i];
		if (ch[i + 1] != '\0') {
			p->next = new str();
			p = p->next;
		}
		else {
			p->next = NULL;
		}
	}
	return *a;
}

int main1() {
	cout << "分别输入要连接的字符串"<<endl;
	string tmp1,tmp2;
	cin >> tmp1 >> tmp2;
	str *st = &create(tmp1.c_str());
	str *st1 = &create(tmp2.c_str());
	conncet(*st, *st1);
	str *p = st;
	while (p != NULL) {
		std::cout << p->ch;
		p = p->next;
	}
	system("pause");
	return 0;
}