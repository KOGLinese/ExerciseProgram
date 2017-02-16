#include <iostream>
#include <cstring>
#include <stack>
#include <time.h> 
#include <stdlib.h>
using namespace std;


template <class T>
void StackClear(stack<T> &s)			//���ջ
{
	while(!s.empty())
		s.pop();
}


/*
�ж϶�ȡ�����ַ��Ƿ��������
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
�Ƚ�ǰ����������������ȼ�
(Ϊ���жϷ��㣬����һ���Ⱥš�=����Ϊ���ʽ�Ķ����)
oper1>=oper2����1
oper1<oper2����-1
oper1��oper2�ֱ�Ϊ�������ŷ���0
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

		case '(':
			if(oper1==')')		//�������Ҳ಻�����ϳ���������
			{
				cout<<"���ʽ��ʽ����\n";
				return 0;
			}
			else
				pri=-1;
			break;

		case ')':
			if(oper1=='(')
				pri=0;		 //�����������
			else
				pri=1;
			break;

		case '=':
			if(oper1=='(')
			{
				cout<<"���Ų�ƥ��\n";
				return 0;
			}
			else if(oper1=='=')
				pri=0;		//�Ⱥ���ԣ�����0
			else
				pri=1;
			break;
	}
	return pri;
}
/*
�����������������������������
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
		//	{
		//		cout<<"��0������\n";
				return 0.1;
		//	}
	}
}

/*
�Զ�λ��������ֵƴ��
*/
/*double NumberSplicing(char ch[])
{
	int dot = 0; 	//�Ƿ�����С����ı�־
	double temp =0;	//��ʱƴ�ӵ���ֵ
	static int len = 10;

	for(int n=0;n<strlen(ch);n++)
	{
		char c = ch[n];
		if(c=='.')
		dot = 1;	//����־��Ϊ1
		else
		{
			c-='0';		//�Ƚ���Ӧ�������ַ�ת��������
			if(dot==0)
				temp = temp *10 + c;
			else
			{
				temp = temp + (double)c/len;  //С�����һλ����x�൱�� x/10;
				len *= 10;					  //С����ĵڶ�λ���൱�� x/100;
				//cout<<"����ת���е��ݴ�ֵ��"<<temp<<endl;
			}
		}

	} 



	return temp;
} */
/*
������ʽ��ֵ��
��ʼ������ջ��һ��������ջ��һ�������ջ��
�������ұ���ÿһ���ַ���������������ѭ�����ԭ�����£�
��1������������ֱ��ѹ������ջ����
��2�������������+-* /��ʱ����������ջΪ�գ���ֱ�ӷŵ�������ջ�������򣬼���3����
��3����������ջ��Ԫ�ص����ȼ��ȵ�ǰ����������ȼ�С����ֱ��ѹ��ջ��������ִ�в��裨4����
��4����������ջ�����������ֲ�����������ջ����������������㣬��������ѹ������ջ�����ظ���2���ͣ�3��
	 ֱ����ǰ�������ѹ�������ջ����
��5�����������š�����ʱ��ֱ��ѹ�������ջ����
��6�����������š�����ʱ�����ε���������ջ�����������������ջ������������֣�ֱ�������Ĳ�����Ϊ�����š�
*/
double CalcExp(char express[])
{
	double a,b;				//����������
	char opera;				//�����
	char c;					//�ַ�����
	char x;					//x������ȡ�����ջջ���������
	stack<char> oper;
	stack<double> data;	//�����ջջ�����������������ջ
	char tempNum[20];		//���λ����Ӧ���ַ�����
	int j=0;
	int i=0, flag=0;		//flag����־�����������λ��
	oper.push('=');			//�Ƚ������(=)���������ջ
	c = express[i++];
	double num=0;
	while(c!='=' || x!='=')			//ѭ��������ʽ�е�ÿ���ַ�
	{
		if(IsOperator(c))	//���������
		{
			//if(flag)		//����������ջ����Ϊ��ȡ������ʱ�����ֲ�û�м�ʱ��������ջ��
		//	{
			//	tempNum[j]=0;					
			//	j=0;
			//	num = NumberSplicing(tempNum);	//����������ʱ������ֵƴ�ӵĽ�����ػ��� 
				//cout << "n----" << num << endl;
			//	data.push(num);			///////////////////////////////////////////////////////////
				num = 0; 				//��ջ֮�����ĳһ�����������ݴ�ֵ
			//	flag = 0;				//�ҽ���־��0����ʾ����������ջ
		//	}
			switch(Priority(x,c))
			{
				case -1:	//��ǰ�����c����ǰһ�����x
					//cout << "o----" << c << endl;
					oper.push(c);		//��ǰ�������ջ/////////////////////////////////
					c=express[i++];		//ȡ���ʽ��һ�ַ�
					break;

				case 0:					//���ţ��Ⱥţ����
					oper.pop();		//�������벿�ֳ�ջ��������
					c=express[i++];		//ȡ���ʽ��һ�ַ�
					break;
				case 1:						//��ǰ�����cС�ڵ���ǰһ�����x
					opera = oper.top();		//��ջ֮ǰȡ��ջ��Ԫ��
					oper.pop();				//�������ջ

					b = data.top();
					data.pop();
					a = data.top();
					data.pop();				//������������ջ
					double t = calculate(a,opera,b);	//������
					data.push(t);		//����������ջ
					break;
			}
		}
		else if(c>='0' && c<='9')	//��������������ַ�(����ջ����Ϊ�����Ƕ�λ���֣�
		{
		//	tempNum[j++] = c;
		//	flag = 1; 				//���ò���������ʾ������δ��ջ
			num=c-'0';
			data.push(num);
			c=express[i++];
		}
	//	else
	//	{
	//		cout<<"��������   ";
	//		return 0;
	//	}
		x = oper.top();		//��ȡ�����ջ����Ԫ��
		//cout<<"ջ���Ĳ�����Ϊ��"<<x<<endl;
	}

		num = data.top();
		
		StackClear(oper);
		StackClear(data);		//�������ջ
		//cout<<num<<endl;

		return 	num;	//��������ջջ��Ԫ�أ���Ϊ������
 
	}

char change(int x)
{
	switch(x)
	{
		case 0:return '+';
		case 1:return '-';
		case 2:return '*';
		default:return '/';
	}
}
int main()
{
	srand((unsigned)time(NULL));
	char express[100];
	int i;
	int n;
	int casenum;
	double anwers[1000];
	char a,b,c,d;
	char e,f,g;
	cout<<"������Ҫ���������⣻"<<endl;
	cin >> n;
	for(i=0;i<n;i++)
	{
		a=rand()%10+48;
		b=rand()%10+48;
		c=rand()%10+48;
		d=rand()%10+48;
		e=change(rand()%4);
		f=change(rand()%4);
		g=change(rand()%4);
		casenum=rand()%6;
		switch(casenum)
		{
			case 0:
			express[0]=a;
			express[1]=e;
			express[2]=b;
			express[3]=f;
			express[4]=c;
			express[5]=g;
			express[6]=d;
			express[7]='=';break;
			case 1:
			express[0]='(';
			express[1]=a;
			express[2]=e;
			express[3]=b;
			express[4]=')';
			express[5]=f;
			express[6]=c;
			express[7]=g;
			express[8]=d;
			express[9]='=';	break;
			case 2:
			express[0]='(';
			express[1]=a;
			express[2]=e;
			express[3]=b;
			express[4]=f;
			express[5]=c;
			express[6]=')';
			express[7]=g;
			express[8]=d;
			express[9]='=';	
			break;
			case 3:
			express[0]=a;
			express[1]=e;
			express[2]='(';
			express[3]=b;
			express[4]=f;
			express[5]=c;
			express[6]=')';
			express[7]=g;
			express[8]=d;
			express[9]='=';
			break;
			case 4:
			express[0]=a;
			express[1]=e;
			express[2]='(';
			express[3]=b;
			express[4]=f;
			express[5]=c;
			express[6]=g;
			express[7]=d;
			express[8]=')';
			express[9]='=';
			break;
			default:
			express[0]=a;
			express[1]=e;
			express[2]=b;
			express[3]=f;
			express[4]='(';
			express[5]=c;
			express[6]=g;
			express[7]=d;
			express[8]=')';
			express[9]=	'=';
			
		}
		anwers[i]=CalcExp(express);
		if(anwers[i]==(int)anwers[i])  
		{
			cout <<"��"<< i+1 <<"��  :"<<express <<endl;
			for(int j=0;j<=9;j++)
			{
			express[j]='\0';
			}
		}
		else
		{
			i=i-1;
			for(int j=0;j<=9;j++)
			{
			express[j]='\0';
			}
			continue;
		}	
	}
		double right=0,wrong=0;
		int inputanwer[1000];
		for(i=0;i<n;i++)
		{	
			cout <<"��" << i+1 << "��𰸣� "; 
			cin >> inputanwer[i];
			if(inputanwer[i]==anwers[i]) right++;
			else wrong++;
		}
		cout << "����"<< right << "��"<<endl; 
		cout << "����"<< wrong << "��"<<endl;
		cout << "��ȷ��Ϊ" << right/n <<endl; 
	return 0;
}
