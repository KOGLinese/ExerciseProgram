#include <iostream>
#include "func.h" 
using namespace std;

int main(int argc, char *argv[])
{

	double right = 0;

	int n;
	char a[4];//������� 

	char oper[3];//��������

	char *ex;

	double answers,inputanswer;//�洢��ȷ��� 
	n = readFile(argv[1]);
	scanf();//��ʼ����

	for (int i = 0; i<n; i++)
	{
		srand((unsigned)time(NULL));//��������ͬ�������

		for (int j = 0; j<4; j++)
			a[j] = randomNumber();//����� 

		for (int j = 0; j<3; j++)
			oper[j] = randomOperation();//����� 

		ex = generateExpression(a, oper);

		answers = calculateResult(ex);//������ȷ�� 	

		if (answers == (int)answers) //����Ƿ����С�� ��������� 
		{
			inputanswer = scanf2(ex, i);//�˻�����
			right += Coutright(answers, inputanswer);//����С������������
			writeFile(argv[2], ex, answers, inputanswer);//���ݵ�д�� 
		}
		else//�����ΪС���������½���ѭ��
			i = i - 1;
		delete[] ex;
	}
 	writeFile2(argv[2],n,right);//�ܽ�д�� 
	print(right, n);//������ 
	return 0;
}
