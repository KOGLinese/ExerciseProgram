#include <iostream>
#include "allfunctions.h" 
int main()
{
	double n,right=0;
	
	char a[4];//������� 
	
	char oper[3];//��������
	 
	char *ex; 
	
	double answers;//�洢��ȷ��� 
	
	n=scanf();//��ʼ����
	
	for(int i=0;i<n;i++)
	{
		srand((unsigned)time(NULL));//��������ͬ�������
		
		for(int j=0;j<4;j++)
			a[j]=randomNumber();//����� 
			
		for(int j=0;j<3;j++)
			oper[j]=randomOperation();//����� 
					
		ex=generateExpression(a,oper);
		
		answers=calculateResult(ex);//������ȷ�� 	

		if(answers==(int)answers) //����Ƿ����С�� ��������� 
		{
			cout << i+1 <<".  "<<ex;
			right+=scanf2(answers);//����С������������
		}
		
		else//�����ΪС���������½���ѭ��
			i=i-1;
		
		delete [] ex;
	}	
	
	print(right,n);//������ 
		
	return 0;
}
