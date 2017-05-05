#include <iostream>
#include <cstring>
#include <stack>
#include <time.h> 
#include <stdlib.h>
#include<fstream>
#include<string>
#include<cmath>
using namespace std;
char language;//输入语言 
template <class T>
void StackClear(stack<T> &s)			//清空栈
{
	while(!s.empty())
		s.pop();
}
/*
判断读取到的字符是否是运算符
*/
int IsOperator(char c)
{
	switch(c)
	{
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
		case ')':
		case '=':
			return 1;
			break;
		default:
			return 0;
			break;
	}
}
/*
比较前后两个运算符的优先级
(为了判断方便，增设一个等号“=”作为表达式的定界符)
oper1>=oper2返回1
oper1<oper2返回-1
oper1、oper2分别为左右括号返回0
*/
int Priority(char oper1,char oper2)
{
	int pri;
	switch(oper2)
	{
		case '+':
		case '-':
			if(oper1=='(' || oper1=='=')
				pri=-1;
			else
				pri=1;
			break;
		case '*':
		case '/':
			if(oper1=='*' || oper1=='/' || oper1==')')
				pri=1;
			else
				pri=-1;
			break;
		case '('://优先级小 
				pri=-1;
			break;

		case ')':
			if(oper1=='(')
				pri=0;		 //左右括号配对
			else
				pri=1;
			break;
		case '=':
			if(oper1=='=')
				pri=0;		//等号配对，返回0
			else
				pri=1;
			break;
	}
	return pri;
}
/*
根据运算符和两个操作数进行运算
*/
double calculate(double a,int oper,double b)
{
	switch(oper)
	{
		case '+': return a+b;
		case '-': return a-b;
		case '*': return a*b;
		case '/':
			if (b!=0)
				return a/b;
			else
				return 0.1;//除0的情况返回成小数，然后在筛选题目时删除 

	}
}
/*
计算表达式的值：
初始化两个栈：一个操作数栈，一个运算符栈。
从左至右遍历每一个字符，遍历过程中遵循步骤和原则如下：
（1）遇到数字则直接压到数字栈顶。
（2）遇到运算符（+-* /）时，若操作符栈为空，则直接放到操作符栈顶，否则，见（3）。
（3）若操作符栈顶元素的优先级比当前运算符的优先级小，则直接压入栈顶，否则执行步骤（4）。
（4）弹出数字栈顶的两个数字并弹出操作符栈顶的运算符进行运算，把运算结果压入数字栈顶，重复（2）和（3）
	 直到当前运算符被压入操作符栈顶。
（5）遇到左括号“（”时则直接压入操作符栈顶。
（6）遇到右括号“）”时则依次弹出操作符栈顶的运算符运算数字栈的最顶上两个数字，直到弹出的操作符为左括号。
*/
double calculateResult(char *express)//用于计算结果 
{
	double a,b;				//两个操作数
	char opera;				//运算符
	char c;					//字符变量
	char x;					//x用来获取运算符栈栈顶的运算符
	stack<char> oper;
	stack<double> data;	//运算符栈栈顶的运算符，操作数栈
	int j=0;
	int i=0;
	oper.push('=');			//先将定界符(=)推入操作符栈
	c = express[i++];
	double num=0;
	while(c!='=' || x!='=')			//循环处理表达式中的每个字符
	{ 
		if(IsOperator(c))	//若是运算符
		{
			num = 0; 				//入栈之后清空某一个操作数的暂存值 
			switch(Priority(x,c))
			{
				case -1:	//当前运算符c大于前一运算符x
					//cout << "o----" << c << endl;
					oper.push(c);		//当前运算符进栈
					c=express[i++];		//取表达式下一字符
					break;

				case 0:					//括号（等号）配对
					oper.pop();		//运算符左半部分出栈（抛弃）
					c=express[i++];		//取表达式下一字符
					break;
				case 1:						//当前运算符c小于等于前一运算符x
					opera = oper.top();		//出栈之前取得栈顶元素
					oper.pop();				//运算符出栈

					b = data.top();
					data.pop();
					a = data.top();
					data.pop();				//两个操作数出栈
					double t = calculate(a,opera,b);	//计算结果
					if(t!=(int)t) 		//解决除0再乘零的情况 
					return 0.1;
					else 
					data.push(t);		//将结算结果入栈
					break;
			}
		}
		else if(c>='0' && c<='9')	//若输入的是数字字符 入栈
		{
			num=c-'0';
			data.push(num);
			c=express[i++];
		}

		x = oper.top();		//获取运算符栈顶的元素
	}
		num = data.top();	
		StackClear(oper);
		StackClear(data);		//清空两个栈
		return 	num;	//返回数字栈栈顶元素，即为计算结果
}

char change(int x)//随机数转变成运算符 
{
	switch(x)
	{
		case 0:return '+';
		case 1:return '-';
		case 2:return '*';
		default:return '/';
	}
}
void Choose(char c,int a)//语言选择 
{
	
	string s;
	int sb;
	ifstream inf;	//读取文件 
	if(c=='C')
		inf.open("e://CAL//Chinese.txt");//语言资源路径 
	if(c=='E')
		inf.open("e://CAL//English.txt");
	if(c=='J')
		inf.open("e://CAL//Japanese.txt");
	if(c=='F')
		inf.open("e://CAL//French.txt");
	if(c=='G')
		inf.open("e://CAL//German.txt");
	switch(a)//判断需输出的文本行 
	{
		case 1:	getline(inf,s,'\n'); 
			   	cout <<s<<endl;
				getline(inf,s,'\n');
				cout <<s<<endl; 
				getline(inf,s,'\n'); 
				cout <<s;
				break;
		case 2:	for(sb=0;sb<4;sb++)
				getline(inf,s,'\n'); 
			   	cout <<s;
				break;
		case 3:	for(sb=0;sb<5;sb++)
				getline(inf,s,'\n'); 
			   	cout <<s<<endl;
				break;
		case 4:	for(sb=0;sb<6;sb++)
				getline(inf,s,'\n'); 
			   	cout <<s;
				break;
	}
	inf.close();//关闭文件	
}
char randomNumber()//用于随机生成数字
{
	return rand()%10+48;
} 
char randomOperation()//用于随机生成运算符
{
	return change(rand()%4);
}
char * generateExpression(char num[],char o[])//用于生成运算式
{
	int casenum;//有无括号的随机情况
	char * express=new char [18];//表达式
	for(int j=0;j<15;j++)
	{
		express[j]='\0';
	}
	casenum=rand()%6;//六种情况 
		switch(casenum)
		{
			case 0://无括号情况 
			express[0]=num[0];
			express[1]=o[0];
			express[2]=num[1];
			express[3]=o[1];
			express[4]=num[2];
			express[5]=o[2];
			express[6]=num[3];
			express[7]='=';
			break;
			case 1://(a o1 b)o2 c o3 g = ?
			express[0]='(';
			express[1]=num[0];
			express[2]=o[0];
			express[3]=num[1];
			express[4]=')';
			express[5]=o[1];
			express[6]=num[2];
			express[7]=o[2];
			express[8]=num[3];
			express[9]='=';	break;
			case 2://(a o1 b o2 c) o3 d = ?
			express[0]='(';
			express[1]=num[0];
			express[2]=o[0];
			express[3]=num[1];
			express[4]=o[1];
			express[5]=num[2];
			express[6]=')';
			express[7]=o[2];
			express[8]=num[3];
			express[9]='=';	
			break;
			case 3://a o1 ( b o2 c) o3 d = ?
			express[0]=num[0];
			express[1]=o[0];
			express[2]='(';
			express[3]=num[1];
			express[4]=o[1];
			express[5]=num[2];
			express[6]=')';
			express[7]=o[2];
			express[8]=num[3];
			express[9]='=';
			break;
			case 4://a o1 (b o2 c o3 d) = ?
			express[0]=num[0];
			express[1]=o[0];
			express[2]='(';
			express[3]=num[1];
			express[4]=o[1];
			express[5]=num[2];
			express[6]=o[2];
			express[7]=num[3];
			express[8]=')';
			express[9]='=';
			break;
			default://a o1 b o2 (c o3 d) =?
			express[0]=num[0];
			express[1]=o[0];
			express[2]=num[1];
			express[3]=o[1];
			express[4]='(';
			express[5]=num[2];
			express[6]=o[2];
			express[7]=num[3];
			express[8]=')';
			express[9]=	'=';
		}
		return express;
}
void scanf()
{
	cout<<"请选择语言类:"<<endl;
	cout<<"C.中文	E.英语	J.日语	F.法语	G.德语" <<endl;
	cin>>language;
	Choose(language,1);
}
int scanf2(int answers)
{
	int inputanswer;//输入的答案
	int inputeranswer;
	cin >> inputanswer;
	if(inputanswer==answers) 
	{
		Choose(language,3);
		return inputanswer*10+1;
	} 
	else 
	{
		Choose(language,2);
		cout << answers<<endl; 
		return inputanswer*10+0;
	}
}
void print(double r,double sum)
{

		Choose(language,4);
		cout << r/sum <<endl;
}
void writeFile(char *s,int n,char * p,double rans,double inans)
{
	ofstream fout;
	fout.open(s);
	fout<<"题目数："<< n<<endl;
	fout<<"表达式："<< p<<endl;
	fout<<"正确答案："<< rans<<endl;
	fout<<"输入的答案："<< inans<<endl; 
	fout.close();
}
string readFile(char * s)
{
	ifstream fin;
	fin.open(s);
	string ch;
	int n;
	getline(fin,ch,'\n');
	fin.close();
	return ch;
}
