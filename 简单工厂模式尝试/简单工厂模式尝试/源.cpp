#include<iostream>
#include<cstdio>
#include <time.h> 
using namespace std;
class Random {                   //基类
private:
	int a;
public:
	Random() {}
	~Random(){}
	virtual int creatrand() { return -1; }   //利用虚函数
	virtual void print(){}
};
class randomNumber :public Random            ///随机数
{
public:
	randomNumber() { cout << "产生随机数： " ; }
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
class randomOperator : public Random     //随机符
{
public:
	randomOperator() { cout << "产生随机运算符： " ; }
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
	Factory * p = new Factory();   //工厂指针
	int k = 0;
	cout << "输入想得到的随机类型,0表示输入结束，1表示生成随机数，2表示生成随机符：\n";
	while (1)
	{
		cin >> k;
		if (k == 0) break;
		Random * rand_ptr = p->produce(k); // 派生类类型选择
		if (rand_ptr == NULL) 
			cout << "不存在该类型重新输入：";
		else 
			rand_ptr->print();   //输出
		cout << endl;
		delete rand_ptr;
	}
	system("pause");
	return 0;
}