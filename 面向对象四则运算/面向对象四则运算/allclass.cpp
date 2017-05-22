#include "allclass.h"
template <class T>
void StackClear(stack<T> &s)			//清空栈
{
	while (!s.empty())
		s.pop();
}
char expresses::change(int x)
{
	switch (x)
	{
	case 0:return '+';
	case 1:return '-';
	case 3:return '*';
	default:return '/';
	}
}
char expresses::randomNumber()
{
	return rand() % 10 + 48;
}
char expresses::randomOperation()
{
	return change(rand() % 4);
}
int	 expresses::IsOperator(char c)//判断是否为运算符
{
	switch (c)
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
int expresses::Priority(char oper1, char oper2)
{
	int pri;
	switch (oper2)
	{
	case '+':
	case '-':
		if (oper1 == '(' || oper1 == '=')
			pri = -1;
		else
			pri = 1;
		break;
	case '*':
	case '/':
		if (oper1 == '*' || oper1 == '/' || oper1 == ')')
			pri = 1;
		else
			pri = -1;
		break;
	case '('://优先级小 
		pri = -1;
		break;

	case ')':
		if (oper1 == '(')
			pri = 0;		 //左右括号配对
		else
			pri = 1;
		break;
	case '=':
		if (oper1 == '=')
			pri = 0;		//等号配对，返回0
		else
			pri = 1;
		break;
	}
	return pri;
}
double expresses::calculate(double a, int oper, double b)
{
	switch (oper)
	{
	case '+':return a + b;
	case '-':return a - b;
	case '*':return a * b;
	case '/':
		if (b != 0)
			return a / b;
		else
			return 0.1;
	}
	return 0;
}
double expresses::calculateResult(char * express)
{
	double a, b;				//两个操作数
	char opera;				//运算符
	char c;					//字符变量
	char x = ' ';					//x用来获取运算符栈栈顶的运算符
	stack<char> oper;
	stack<double> data;	//运算符栈栈顶的运算符，操作数栈
	int j = 0;
	int i = 0;
	oper.push('=');			//先将定界符(=)推入操作符栈
	c = express[i++];
	double num = 0;
	while (c != '=' || x != '=')			//循环处理表达式中的每个字符
	{
		if (IsOperator(c))	//若是运算符
		{
			num = 0; 				//入栈之后清空某一个操作数的暂存值 
			switch (Priority(x, c))
			{
			case -1:	//当前运算符c大于前一运算符x
						//cout << "o----" << c << endl;
				oper.push(c);		//当前运算符进栈
				c = express[i++];		//取表达式下一字符
				break;

			case 0:					//括号（等号）配对
				oper.pop();		//运算符左半部分出栈（抛弃）
				c = express[i++];		//取表达式下一字符
				break;
			case 1:						//当前运算符c小于等于前一运算符x
				opera = oper.top();		//出栈之前取得栈顶元素
				oper.pop();				//运算符出栈

				b = data.top();
				data.pop();
				a = data.top();
				data.pop();				//两个操作数出栈
				double t = calculate(a, opera, b);	//计算结果
				if (t != (int)t) 		//解决除0再乘零的情况 
					return 0.1;
				else
					data.push(t);		//将结算结果入栈
				break;
			}
		}
		else if (c >= '0' && c <= '9')	//若输入的是数字字符 入栈
		{
			num = c - '0';
			data.push(num);
			c = express[i++];
		}

		x = oper.top();		//获取运算符栈顶的元素
	}
	num = data.top();
	StackClear(oper);
	StackClear(data);		//清空两个栈
	return 	num;	//返回数字栈栈顶元素，即为计算结果
}
bool expresses::IsInt(double answer)
{
	if (answer == (int)answer) return true;
	else return false;
}
char * expresses:: generateExpression()
{
	srand((unsigned)time(NULL));//不出现相同的随机数
	for (int i = 0; i < 4; i++)
	{
		a[i] = randomNumber();
	}
	for (int i = 0; i < 3; i++)
	{
		o[i] = randomOperation();
	}
	int casenum;//有无括号的随机情况
	char * express = new char[18];//表达式
	for (int j = 0; j<15; j++)
	{
		express[j] = '\0';
	}
	casenum = rand() % 6;//六种情况 
	switch (casenum)
	{
	case 0://无括号情况 
		express[0] = a[0];
		express[1] = o[0];
		express[2] = a[1];
		express[3] = o[1];
		express[4] = a[2];
		express[5] = o[2];
		express[6] = a[3];
		express[7] = '=';
		break;
	case 1://(a o1 b)o2 c o3 g = ?
		express[0] = '(';
		express[1] = a[0];
		express[2] = o[0];
		express[3] = a[1];
		express[4] = ')';
		express[5] = o[1];
		express[6] = a[2];
		express[7] = o[2];
		express[8] = a[3];
		express[9] = '=';	break;
	case 2://(a o1 b o2 c) o3 d = ?
		express[0] = '(';
		express[1] = a[0];
		express[2] = o[0];
		express[3] = a[1];
		express[4] = o[1];
		express[5] = a[2];
		express[6] = ')';
		express[7] = o[2];
		express[8] = a[3];
		express[9] = '=';
		break;
	case 3://a o1 ( b o2 c) o3 d = ?
		express[0] = a[0];
		express[1] = o[0];
		express[2] = '(';
		express[3] = a[1];
		express[4] = o[1];
		express[5] = a[2];
		express[6] = ')';
		express[7] = o[2];
		express[8] = a[3];
		express[9] = '=';
		break;
	case 4://a o1 (b o2 c o3 d) = ?
		express[0] = a[0];
		express[1] = o[0];
		express[2] = '(';
		express[3] = a[1];
		express[4] = o[1];
		express[5] = a[2];
		express[6] = o[2];
		express[7] = a[3];
		express[8] = ')';
		express[9] = '=';
		break;
	default://a o1 b o2 (c o3 d) =?
		express[0] = a[0];
		express[1] = o[0];
		express[2] = a[1];
		express[3] = o[1];
		express[4] = '(';
		express[5] = a[2];
		express[6] = o[2];
		express[7] = a[3];
		express[8] = ')';
		express[9] = '=';
	}
	return express;
}



void Language::set(char c)
{
	language = c;
	Choose(1);
}
void Language::scanf() {
	cout << "请选择语言类:" << endl;
	cout << "C.中文	E.英语	J.日语	F.法语	G.德语" << endl;
}
void Language::scanf2(char * p, int i)
{
	cout << i + 1 << ".  " << p;
}
void Language::Choose(int a)
{
	string s;
	int sb;
	//ifstream inf;	//读取文件 
	if (language == 'C')
		inf.open("e://CAL//Chinese.txt");//语言资源路径 
	if (language == 'E')
		inf.open("e://CAL//English.txt");
	if (language == 'J')
		inf.open("e://CAL//Japanese.txt");
	if (language == 'F')
		inf.open("e://CAL//French.txt");
	if (language == 'G')
		inf.open("e://CAL//German.txt");
	switch (a)//判断需输出的文本行 
	{
	case 1:	getline(inf, s, '\n');
		cout << s << endl;
		getline(inf, s, '\n');
		cout << s << endl;
		getline(inf, s, '\n');
		cout << s;
		break;
	case 2:	for (sb = 0; sb<4; sb++)
		getline(inf, s, '\n');
		cout << s;
		break;
	case 3:	for (sb = 0; sb<5; sb++)
		getline(inf, s, '\n');
		cout << s << endl;
		break;
	case 4:	for (sb = 0; sb<6; sb++)
		getline(inf, s, '\n');
		cout << s;
		break;
	}
	inf.close();//关闭文件	
}
void Language::print(double r, double sum)
{
	Choose(4);
	cout << r / sum << endl;
}



void R_and_W::set(double ans )
{
	inputanswer = ans;
}
int R_and_W::readFile(char * s)
{
	fin.open(s, ios::in);
	int n;
	fin >> n;
	fin.close();
	return n;
}
void R_and_W::writeFile1(char *s, char * p, double rans, double inans)
{
	fout.open(s, ios::app);
	fout << "表达式：" << p << endl;
	fout << "正确答案：" << rans << endl;
	fout << "输入的答案：" << inans << endl << endl;
	fout.close();
}
void R_and_W::writeFile2(char *s,double right)
{
	fout.open(s, ios::app);
	fout << "\n以上总题数为: " << n << endl;
	fout << "答对题数：" << right << endl;
	fout << "正确率为：" << right / n << endl << endl;
	fout.close();
}
int R_and_W::Countright(double answers,double inputanswer,Language &l)
{
	if (inputanswer == answers)
	{
		l.Choose(3);
		return  1;
	}
	else
	{
		l.Choose(2);
		cout << answers << endl;
		return 0;
	}
}