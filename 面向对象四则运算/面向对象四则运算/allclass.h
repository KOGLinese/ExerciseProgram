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
		Random(){}
		~Random(){}
		virtual char get_rand(int k) { return ' '; }
		virtual int create() {	return -1;	}
};
class randomNumber :public Random
{
	public:
		randomNumber(){}
		~randomNumber(){}
		virtual int create();
		virtual char get_rand(int k);
};
class randomOperator : public Random
{
public:
	randomOperator(){}
	~randomOperator(){}
	virtual int create();
	virtual char get_rand(int k);
};
class Language {
	private:
	char language;
	ifstream inf;//��ȡ�����ļ�
	public:
		void set(char c);//��紫��
		void scanf();//��ʼ������'
		void scanf2(char * p, int i);
		void print(double r, double sum);//
		void Choose(int a);//����ѡ���Լ�ѡ����� ������
};
class R_and_W//��ȡ��
{
	private:
	int n;//��������
	ifstream fin;//��ȡ�����ļ�
	ofstream fout;//�ļ���
	double inputanswer;
	public :
	void set(double ans);
	int readFile(char *s);//��ȡ����
	void writeFile1(char *s, char * p, double rans, double inans);//ÿ����� ����out
	void writeFile2(char *s, double right);//����ܽ����
	int Countright(double answers, double inputanswer, Language &l);//����
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