#include<fstream>
#include<iostream> 
using namespace std;
void writeFile(char *s, char * p, double rans, double inans)
{
	ofstream fout;
	fout.open(s,ios::app);
	fout<< "���ʽ��" << p << endl;
	fout<< "��ȷ�𰸣�" << rans << endl;
	fout<< "����Ĵ𰸣�" << inans << endl;
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
