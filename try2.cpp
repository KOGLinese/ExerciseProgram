#include<fstream>
#include<iostream> 
using namespace std;
void writeFile(char *s, char * p, double rans, double inans)
{
	ofstream fout;
	fout.open(s,ios::app);
	fout<< "表达式：" << p << endl;
	fout<< "正确答案：" << rans << endl;
	fout<< "输入的答案：" << inans << endl;
	fout.close();
}
int main(int argc,char * argv[])
{
	char e[100];
	double rans;
	double inans;
	for(int i=0;i<5;i++)
	{
		cin>>e>>rans>>inans;
		writeFile(argv[1],e,rans,inans); 
	}
	return 0;
} 
