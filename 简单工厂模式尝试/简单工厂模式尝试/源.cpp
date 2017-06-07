#include<iostream>
#include<cstdio>
#include <time.h> 
using namespace std;
class Random {                   //����
private:
	int a;
public:
	Random() {}
	~Random(){}
	virtual int creatrand() { return -1; }   //�����麯��
	virtual void print(){}
};
class randomNumber :public Random            ///�����
{
public:
	randomNumber() { cout << "����������� " ; }
	~randomNumber(){}
	virtual void print() {
		cout << changeNum(creatrand());
	}
	char changeNum(int k)
	{
		return k + 48;
	}
	virtual int creatrand();
};
int randomNumber::creatrand()
{
	return rand() % 10;
}
class randomOperator : public Random     //�����
{
public:
	randomOperator() { cout << "�������������� " ; }
	~randomOperator(){}
	virtual int creatrand();
	virtual void print() {
		cout << changeOper(creatrand());
	}
	char changeOper(int k);
};
char randomOperator::changeOper(int k)
{
		switch (k)
		{
		case 0:return '+';
		case 1:return '-';
		case 2:return '*';
		case 3:return '/';
		default:return ' ';
		}
}
int  randomOperator::creatrand()
{
	return rand() % 4;
}
class Factory {
public:
	Factory(){}
	~Factory(){}
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
int main()
{
	Factory * p = new Factory();   //����ָ��
	int k = 0;
	cout << "������õ����������,0��ʾ���������1��ʾ�����������2��ʾ�����������\n";
	while (1)
	{
		cin >> k;
		if (k == 0) break;
		Random * rand_ptr = p->produce(k); // ����������ѡ��
		if (rand_ptr == NULL) 
			cout << "�����ڸ������������룺";
		else 
			rand_ptr->print();   //���
		cout << endl;
		delete rand_ptr;
	}
	system("pause");
	return 0;
}