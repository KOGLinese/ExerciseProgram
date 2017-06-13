
// sb.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "sb.h"
#include "sbDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CsbApp

BEGIN_MESSAGE_MAP(CsbApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CsbApp ����

CsbApp::CsbApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CsbApp ����

CsbApp theApp;


// CsbApp ��ʼ��

BOOL CsbApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CsbDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

template <class T>
void StackClear(stack<T> &s)			//���ջ
{
	while (!s.empty())
		s.pop();
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
bool expresses::IsInt(double answer)
{
	if (answer == (int)answer) return true;
	else return false;
}
char * expresses::generateExpression()
{
	RandomFactory * fptr = new RandomFactory();

	srand((unsigned)time(NULL));//��������ͬ�������
	for (int i = 0; i < 4; i++)
	{
		Random * rand_ptr = fptr->produce(1);
		a[i] = rand_ptr->get_rand(rand_ptr->create());
		delete rand_ptr;
	}
	for (int i = 0; i < 3; i++)
	{
		Random * rand_ptr = fptr->produce(2);
		o[i] = rand_ptr->get_rand(rand_ptr->create());
		delete rand_ptr;
	}
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


int randomNumber::create()
{
	return rand() % 10;
}
int  randomOperator::create()
{
	return rand() % 4;
}
char randomOperator::get_rand(int k)
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
char randomNumber::get_rand(int k)
{
	return k + 48;
}
