#include <iostream>
#include "func.h" 
using namespace std;

int main(int argc, char *argv[])
{

	double right = 0;

	int n;
	char a[4];//随机整数 

	char oper[3];//随机运算符

	char *ex;

	double answers,inputanswer;//存储正确结果 
	n = readFile(argv[1]);
	scanf();//开始界面

	for (int i = 0; i<n; i++)
	{
		srand((unsigned)time(NULL));//不出现相同的随机数

		for (int j = 0; j<4; j++)
			a[j] = randomNumber();//随机数 

		for (int j = 0; j<3; j++)
			oper[j] = randomOperation();//运算符 

		ex = generateExpression(a, oper);

		answers = calculateResult(ex);//储存正确答案 	

		if (answers == (int)answers) //检查是否存在小数 ，结果检验 
		{
			inputanswer = scanf2(ex, i);//人机交互
			right += Coutright(answers, inputanswer);//不是小数则进行输入答案
			writeFile(argv[2], ex, answers, inputanswer);//内容的写入 
		}
		else//如果答案为小数，则重新进行循环
			i = i - 1;
		delete[] ex;
	}
 	writeFile2(argv[2],n,right);//总结写入 
	print(right, n);//结果诊断 
	return 0;
}
