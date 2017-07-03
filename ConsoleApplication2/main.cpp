#include "stu.h"
#include <iostream>
#include <vector>
void input();
void display();
vector<Student*> stu(NULL);

int main()
{	
	input();
	return 0;
}

void display() 
{
	for (int i = 0; i < stu.size();i++) 
	{
		stu[i]->Display();
	}
}

void input()
{
	int count = 0, age;
	string num, name, sex;
	float score1, score2, score3;
	Student *tmp = NULL;
	cout << "请输入学生人数" << endl;
	cin >> count;
	for (int i = 0; i < count; i++)
	{
		tmp = new Student;
		cout << "输入学生成绩：" << endl << "学号 姓名 性别 年龄 成绩1 成绩2 成绩3";
		cin >> num >> name >> sex >> age >> score1 >> score2 >> score3;
		tmp->Input(num, name, sex, age, score1, score2, score3);
		stu.push_back(tmp);
	}
}
