#include <iostream>
#include <cstring>
#include <stack>
#include <time.h> 
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;
int IsOperator(char c);// �ж��Ƿ�Ϊ����� 
int Priority(char oper1, char oper2);//������Ƚ� 
double calculate(double a, int oper, double b);//�������ļ��� 
double calculateResult(char *express);//���ڼ�����
char change(int x);//�����ת�������� 
char randomNumber();//���������������
char randomOperation();//����������������
char * generateExpression(char num[], char o[]);//������������ʽ
void scanf();
int Coutright(double answers,double inputerswner);
void print(double r, double sum);
void writeFile(char *s, char * p, double rans, double inans);
int readFile(char * s);
double scanf2(char * p, int i);//�����
void Choose(char c, int a);//����ѡ�� 
void writeFile2(char *s,double n,double right);