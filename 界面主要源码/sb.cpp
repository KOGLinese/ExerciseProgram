
// sb.cpp : 定义应用程序的类行为。
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


// CsbApp 构造

CsbApp::CsbApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CsbApp 对象

CsbApp theApp;


// CsbApp 初始化

BOOL CsbApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CsbDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

template <class T>
void StackClear(stack<T> &s)			//清空栈
{
	while (!s.empty())
		s.pop();
}
int	 expresses::IsOperator(char c)//判断是否为运算符
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
	case '('://优先级小 
		pri = -1;
		break;

	case ')':
		if (oper1 == '(')
			pri = 0;		 //左右括号配对
		else
			pri = 1;
		break;
	case '=':
		if (oper1 == '=')
			pri = 0;		//等号配对，返回0
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
	double a, b;				//两个操作数
	char opera;				//运算符
	char c;					//字符变量
	char x = ' ';					//x用来获取运算符栈栈顶的运算符
	stack<char> oper;
	stack<double> data;	//运算符栈栈顶的运算符，操作数栈
	int j = 0;
	int i = 0;
	oper.push('=');			//先将定界符(=)推入操作符栈
	c = express[i++];
	double num = 0;
	while (c != '=' || x != '=')			//循环处理表达式中的每个字符
	{
		if (IsOperator(c))	//若是运算符
		{
			num = 0; 				//入栈之后清空某一个操作数的暂存值 
			switch (Priority(x, c))
			{
			case -1:	//当前运算符c大于前一运算符x
						//cout << "o----" << c << endl;
				oper.push(c);		//当前运算符进栈
				c = express[i++];		//取表达式下一字符
				break;

			case 0:					//括号（等号）配对
				oper.pop();		//运算符左半部分出栈（抛弃）
				c = express[i++];		//取表达式下一字符
				break;
			case 1:						//当前运算符c小于等于前一运算符x
				opera = oper.top();		//出栈之前取得栈顶元素
				oper.pop();				//运算符出栈

				b = data.top();
				data.pop();
				a = data.top();
				data.pop();				//两个操作数出栈
				double t = calculate(a, opera, b);	//计算结果
				if (t != (int)t) 		//解决除0再乘零的情况 
					return 0.1;
				else
					data.push(t);		//将结算结果入栈
				break;
			}
		}
		else if (c >= '0' && c <= '9')	//若输入的是数字字符 入栈
		{
			num = c - '0';
			data.push(num);
			c = express[i++];
		}

		x = oper.top();		//获取运算符栈顶的元素
	}
	num = data.top();
	StackClear(oper);
	StackClear(data);		//清空两个栈
	return 	num;	//返回数字栈栈顶元素，即为计算结果
}
bool expresses::IsInt(double answer)
{
	if (answer == (int)answer) return true;
	else return false;
}
char * expresses::generateExpression()
{
	RandomFactory * fptr = new RandomFactory();

	srand((unsigned)time(NULL));//不出现相同的随机数
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
	int casenum;//有无括号的随机情况
	char * express = new char[18];//表达式
	for (int j = 0; j<15; j++)
	{
		express[j] = '\0';
	}
	casenum = rand() % 6;//六种情况 
	switch (casenum)
	{
	case 0://无括号情况 
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
