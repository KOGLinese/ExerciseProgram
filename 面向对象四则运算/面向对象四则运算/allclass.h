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
	char a[4];
	char o[3];
	char change(int x);
	char randomNumber();
	char randomOperation();
	int IsOperator(char c);
	int Priority(char oper1, char oper2);
	double calculate(double a, int oper, double b);
public:
	double calculateResult(char * express);
	char * generateExpression();
};

class Language {
private:
	char language;
	ifstream inf;//读取语言文件
public:
		void set(char c);//外界传入
		void scanf();//初始化界面
		void Choose(int a);//语言选择，以及选择输出 结果情况
};
class R_and_W//读取类
{
private:
	int n;//题数传入
	ifstream fin;//读取题数文件
	ofstream fout;
	double inputanswer;
public :
	void set(double ans);
	int readFile(char *s);
	void writeFile1(char *s, char * p, double rans, double inans);
	void writeFile2(char *s, double right);
	int Countright(double answers, Language l, char c);
};