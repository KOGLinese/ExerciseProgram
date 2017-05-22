#include "allclass.h"
template <class T>
void StackClear(stack<T> &s)			//���ջ
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
int	 expresses::IsOperator(char c)//�ж��Ƿ�Ϊ�����
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
	case '('://���ȼ�С 
		pri = -1;
		break;

	case ')':
		if (oper1 == '(')
			pri = 0;		 //�����������
		else
			pri = 1;
		break;
	case '=':
		if (oper1 == '=')
			pri = 0;		//�Ⱥ���ԣ�����0
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
	double a, b;				//����������
	char opera;				//�����
	char c;					//�ַ�����
	char x = ' ';					//x������ȡ�����ջջ���������
	stack<char> oper;
	stack<double> data;	//�����ջջ�����������������ջ
	int j = 0;
	int i = 0;
	oper.push('=');			//�Ƚ������(=)���������ջ
	c = express[i++];
	double num = 0;
	while (c != '=' || x != '=')			//ѭ��������ʽ�е�ÿ���ַ�
	{
		if (IsOperator(c))	//���������
		{
			num = 0; 				//��ջ֮�����ĳһ�����������ݴ�ֵ 
			switch (Priority(x, c))
			{
			case -1:	//��ǰ�����c����ǰһ�����x
						//cout << "o----" << c << endl;
				oper.push(c);		//��ǰ�������ջ
				c = express[i++];		//ȡ���ʽ��һ�ַ�
				break;

			case 0:					//���ţ��Ⱥţ����
				oper.pop();		//�������벿�ֳ�ջ��������
				c = express[i++];		//ȡ���ʽ��һ�ַ�
				break;
			case 1:						//��ǰ�����cС�ڵ���ǰһ�����x
				opera = oper.top();		//��ջ֮ǰȡ��ջ��Ԫ��
				oper.pop();				//�������ջ

				b = data.top();
				data.pop();
				a = data.top();
				data.pop();				//������������ջ
				double t = calculate(a, opera, b);	//������
				if (t != (int)t) 		//�����0�ٳ������� 
					return 0.1;
				else
					data.push(t);		//����������ջ
				break;
			}
		}
		else if (c >= '0' && c <= '9')	//��������������ַ� ��ջ
		{
			num = c - '0';
			data.push(num);
			c = express[i++];
		}

		x = oper.top();		//��ȡ�����ջ����Ԫ��
	}
	num = data.top();
	StackClear(oper);
	StackClear(data);		//�������ջ
	return 	num;	//��������ջջ��Ԫ�أ���Ϊ������
}
char * expresses:: generateExpression()
{
	int casenum;//�������ŵ�������
	char * express = new char[18];//���ʽ
	for (int j = 0; j<15; j++)
	{
		express[j] = '\0';
	}
	casenum = rand() % 6;//������� 
	switch (casenum)
	{
	case 0://��������� 
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
	cout << "��ѡ��������:" << endl;
	cout << "C.����	E.Ӣ��	J.����	F.����	G.����" << endl;
	
	
}
void Language::Choose(int a)
{
	string s;
	int sb;
	//ifstream inf;	//��ȡ�ļ� 
	if (language == 'C')
		inf.open("e://CAL//Chinese.txt");//������Դ·�� 
	if (language == 'E')
		inf.open("e://CAL//English.txt");
	if (language == 'J')
		inf.open("e://CAL//Japanese.txt");
	if (language == 'F')
		inf.open("e://CAL//French.txt");
	if (language == 'G')
		inf.open("e://CAL//German.txt");
	switch (a)//�ж���������ı��� 
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
	inf.close();//�ر��ļ�	
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
	fout << "���ʽ��" << p << endl;
	fout << "��ȷ�𰸣�" << rans << endl;
	fout << "����Ĵ𰸣�" << inans << endl << endl;
	fout.close();
}
void R_and_W::writeFile2(char *s,double right)
{
	fout.open(s, ios::app);
	fout << "\n����������Ϊ: " << n << endl;
	fout << "���������" << right << endl;
	fout << "��ȷ��Ϊ��" << right / n << endl << endl;
	fout.close();
}
int R_and_W::Countright(double answers,Language l,char c)
{
	l.set(c);
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