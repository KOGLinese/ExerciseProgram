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
	ifstream inf;//读取语言文件
	public:
		void set(char c);//外界传入
		void scanf();//初始化界面'
		void scanf2(char * p, int i);
		void print(double r, double sum);//
		void Choose(int a);//语言选择，以及选择输出 结果情况
};
class R_and_W//读取类
{
	private:
	int n;//题数传入
	ifstream fin;//读取题数文件
	ofstream fout;//文件流
	double inputanswer;
	public :
	void set(double ans);
	int readFile(char *s);//读取题数
	void writeFile1(char *s, char * p, double rans, double inans);//每次情况 存入out
	void writeFile2(char *s, double right);//情况总结存入
	int Countright(double answers, double inputanswer, Language &l);//计数
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