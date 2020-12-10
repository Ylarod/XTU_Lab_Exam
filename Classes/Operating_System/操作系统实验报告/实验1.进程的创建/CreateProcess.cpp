#include <bits/stdc++.h>
#include <windows.h>	//Win32 API
#define MAX_LINE_LEN 128
void NewProc(char*);	// 声明函数
using namespace std;
char cmdline[MAX_LINE_LEN];
int main()
{
	char ch;
	ifstream fid;
	HWND hWindow;
	hWindow=GetForegroundWindow();//获取本程序运行窗口的句柄
	//改变本程序运行窗口的位置和大小使之与子进程窗口整齐排列
	MoveWindow(hWindow,10,10,425,320,TRUE);
	fid.open("cmdline.txt");//打开存储命令行的文件
	if (!fid)	//若文件不存在，报错
	{
		cout<<"Can't open cmdline.txt !"<<endl;
		ch=cin.get();
		exit(0);
	}
	//从文件逐条读出命令行，用于创建进程
	while (fid.getline(cmdline,MAX_LINE_LEN)) {
		cout<<"cmdline="<<cmdline<<endl;//输出所读命令行
		NewProc(cmdline);//创建新进程
	}
	cout<<"\nEnd"<<endl;
	return 0;
}
void NewProc(char* cmdline)
{
	static int counter=1;
	STARTUPINFO si={sizeof(STARTUPINFO)};
	//使成员dwX,dwY和dwXSize,dwYSize有效
	//目的是为了能调整各进程窗口位置和大小
	si.dwFlags=STARTF_USEPOSITION|STARTF_USESIZE;
	si.dwXSize=400;	//窗口宽
	si.dwYSize=260;	//窗口高
	PROCESS_INFORMATION pi;
	DWORD dwx=10,dwy=10;	//窗口左上角位置
	switch (counter%4)
	{
	case 0 : si.dwX=dwx;	//指定第四个子进程的窗口的左上角位置
			 si.dwY=dwy;
			 break;
	case 1 : si.dwX=dwx+425;//指定第一个子进程的窗口的左上角位置
			 si.dwY=dwy;
			 break;
	case 2 : si.dwX=dwx;	//指定第二个子进程的窗口的左上角位置
			 si.dwY=dwy+310;
			 break;
	case 3 : si.dwX=dwx+425;//指定第三个子进程的窗口的左上角位置
			 si.dwY=dwy+310;
			 break;
	}
	counter++;
	BOOL result=CreateProcess(
		NULL,			//没指定可执行模块名
		cmdline,		//路径和可执行模块名
		NULL,			//子进程不能继承此函数返回的句柄
		NULL,			//子进程的线程不能继承此函数返回的句柄
		FALSE,			//新进程不能从调用此函数进程继承此句柄
		NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,
						//创建一个没有特殊调度需求的普通进程、开辟新窗口
		NULL,			//新进程使用调用此函数进程(父进程)的环境块
		NULL,			//新进程使用父进程的当前目录作为自己的当前目录
		&si,			//STARTUPINFO结构决定新进程主窗口如何出现(显示)
		&pi		//PROCESS_INFORMATION结构用于接收新进程的标识信息
		);
	//显示详细的创建进程出错信息
	if (GetLastError()) {
		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
			(LPSTR) &lpMsgBuf,
			0,
			NULL
			);
		//弹出出错窗口指示错误(该信息由FormatMessage存入了lpMsgBuf中)
		MessageBox(NULL,(LPSTR)lpMsgBuf,"Error",MB_OK | MB_ICONINFORMATION);
		LocalFree(lpMsgBuf);
		//释放在FormatMessage中动态分配的空间
	}
}
