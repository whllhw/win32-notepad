#include "stu.h"
#include<sstream>

template <typename T>

string int2str(T i) {
	string b;
	stringstream ss;
	ss << i;
	ss >> b;
	return b;
}

void Student::Input(string num, string name, string sex, int age, float score1, float score2, float score3)
{
	this->num = num;
	this->name = name;
	this->sex = sex;
	this->age = age;
	this->score1 = score1;
	this->score2 = score2;
	this->score3 = score3;
}

bool Student::GetFaild()
{
	if (score1 < 60)
		if (score2 < 60)
			if (score3 < 60)
				return true;
	return false;
}

float Student::GetAverage()
{
	return (score1 + score2 + score3) / 3;
}

void Student::Display() {
	cout.precision(1);
	cout << num<<'  '<<name<<'  '<<sex<<'  '<<age<<'  '<<score1<<' '<<score2<<'  '<<score3<<endl;
}