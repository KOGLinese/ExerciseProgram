#include <iostream>
#include "allfunctions.h" 
int main(int argc,char *argv[])
{
	
	double right=0;
	
	int n;
	char a[4];//������� 
	
	char oper[3];//��������
	 
	char *ex; 
	
	double answers;//�洢��ȷ��� 
	n=atoi(readFile(argv[1]).c_str());
	scanf();//��ʼ����
	
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
			right+=scanf2(answers)%10;//����С������������
			
			writeFile(argv[2],n,ex,(int)answers,(int)(scanf2(answers)/10));
		}
		
		else//�����ΪС���������½���ѭ��
			i=i-1;
		
		delete [] ex;
	}	
	
	print(right,n);//������ 
		
	return 0;
}
