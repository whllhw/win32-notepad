#pragma once
#include<string>
#include <iostream>
using namespace std;
class Student {
protected:
	string num;
	string name;
	string sex;
	int age;
	float score1;
	float score2;
	float score3;

public:
	Student(): 
		num(NULL),name(NULL),sex(NULL),age(0),score1(0),score2(0),score3(0)
	{
	}
	void Input(string num,string name,string sex,int age,float score1,float score2 ,float score3);
	bool GetFaild();
	float GetAverage();
	void Display();
};