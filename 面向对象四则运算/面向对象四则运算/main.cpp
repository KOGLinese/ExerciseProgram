#include<iostream>
using namespace std;
#include "allclass.h"
int main(int argc,char *argv[])
{
	expresses ex;
	Language lan;
	R_and_W file;
	int cal_num,i,j,k;
	double rightans=0;
	double inputans=0;
	int right_num=0;
	char * express=NULL;
	lan.scanf();
	char c;
	cin >> c;
	lan.set(c);
	//cin >> cal_num;
	cal_num=file.readFile(argv[1]);
	for (i = 0; i < cal_num; i++)
	{
		express = ex.generateExpression();
		rightans = ex.calculateResult(express);
		if (ex.IsInt(rightans)) {
			lan.scanf2(express, i);
			cin >> inputans;
		right_num += file.Countright(rightans, inputans, lan);
			file.writeFile1(argv[2], express, rightans, inputans);
		}
		else i = i - 1;
		delete[] express;
	}
	file.writeFile2(express, right_num);
	lan.print(right_num, cal_num);
}