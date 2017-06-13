
// sb.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include <iostream>
#include <cstring>
#include <stack>
#include <time.h> 
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;
class expresses {
private:
	char a[4];//数字
	char o[3];//运算符
	int IsOperator(char c);//内部判断否为运算符
	int Priority(char oper1, char oper2);//比较优先级
	double calculate(double a, int oper, double b);//计算
public:
	double calculateResult(char * express);//计算表达式
	bool IsInt(double answer);//判断答案是否为整数
	char * generateExpression();//表达式
};
class Random {
public:
	Random() {}
	~Random() {}
	virtual char get_rand(int k) { return ' '; }
	virtual int create() { return -1; }
};
class randomNumber :public Random
{
public:
	randomNumber() {}
	~randomNumber() {}
	virtual int create();
	virtual char get_rand(int k);
};
class randomOperator : public Random
{
public:
	randomOperator() {}
	~randomOperator() {}
	virtual int create();
	virtual char get_rand(int k);
};
class RandomFactory
{
public:
	RandomFactory() {}
	~RandomFactory() {}
	Random * produce(int k)
	{
		switch (k)
		{
		case 1:return new randomNumber();
		case 2:return new randomOperator();
		default:return NULL;
		}
	}
};

// CsbApp: 
// 有关此类的实现，请参阅 sb.cpp
//

class CsbApp : public CWinApp
{
public:
	CsbApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CsbApp theApp;
