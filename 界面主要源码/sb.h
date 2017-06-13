
// sb.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
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
	char a[4];//����
	char o[3];//�����
	int IsOperator(char c);//�ڲ��жϷ�Ϊ�����
	int Priority(char oper1, char oper2);//�Ƚ����ȼ�
	double calculate(double a, int oper, double b);//����
public:
	double calculateResult(char * express);//������ʽ
	bool IsInt(double answer);//�жϴ��Ƿ�Ϊ����
	char * generateExpression();//���ʽ
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
// �йش����ʵ�֣������ sb.cpp
//

class CsbApp : public CWinApp
{
public:
	CsbApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CsbApp theApp;
