#include <iostream>
#include <cstring>
#include <stack>
#include <time.h> 
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;
int IsOperator(char c);// 判断是否为运算符 
int Priority(char oper1, char oper2);//运算符比较 
double calculate(double a, int oper, double b);//两个数的计算 
double calculateResult(char *express);//用于计算结果
char change(int x);//随机数转变成运算符 
char randomNumber();//用于随机生成数字
char randomOperation();//用于随机生成运算符
char * generateExpression(char num[], char o[]);//用于生成运算式
void scanf();
int Coutright(double answers,double inputerswner);
void print(double r, double sum);
void writeFile(char *s, char * p, double rans, double inans);
int readFile(char * s);
double scanf2(char * p, int i);//输入答案
void Choose(char c, int a);//语言选择 
void writeFile2(char *s,double n,double right);
