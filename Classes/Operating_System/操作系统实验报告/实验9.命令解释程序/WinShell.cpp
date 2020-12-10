#define _Win32_WINNT 0x0501
#include <stdlib.h>		//atoi()等
#include <iostream>
#include <windows.h>	//DWORD;HANDLE...其中还有许多头文件
#include <tlhelp32.h>	//CreateToolhelp32Snapshot()
#include <string.h>
#include "WinShell.h"
using namespace std;

// 以下两个函数在主函数开头声明后放在主函数后面不行，故将它们移
// 至mian()的前面，原因可能是它们的参数类型分别是FILETIME和DWORD

// ***************** 时间处理函数 ******************
void ftime(FILETIME filetime)
{
	SYSTEMTIME systemtime;
	if (filetime.dwLowDateTime == -1)	// Win32时间的低32位
		cout << "Never Expires\n";
	else
	{
		//将UTC(Universal Time Coordinated)文件时间转换成本地文件时间
		if (FileTimeToLocalFileTime(&filetime, &filetime) != 0)
		{
			//将64位时间转化成系统时间
			if (FileTimeToSystemTime(&filetime, &systemtime) != 0)
			{
				//以一定能格式输出时间
				cout.fill('0');	//不足指定宽度是用0填充
				cout << dec << systemtime.wYear << '-';
				cout.width(2); cout << systemtime.wMonth << '-';	//月份用2位显示，下类似
				cout.width(2); cout << systemtime.wDay << "  ";
				cout.width(2); cout << systemtime.wHour << ':';
				cout.width(2); cout << systemtime.wMinute;
			}
			else
				cout << "FileTimeToSystemTime failed\n";
		}
		else
			cout << "FileTimeToLocalFileTime failed\n";
	}
	cout.fill(' ');	//恢复空格填充
}

// ************ 回调函数 ************
BOOL WINAPI ConsoleHandler(DWORD CEvent)
{	// 此函数不做什么，由系统处理事件，包括按下Ctrl+C等
	switch (CEvent)
	{
	case CTRL_C_EVENT:
		break;
	case CTRL_BREAK_EVENT:
		break;
	case CTRL_CLOSE_EVENT:
		break;
	case CTRL_LOGOFF_EVENT:
		break;
	case CTRL_SHUTDOWN_EVENT:
		break;
	}
	return TRUE;
}

// **************** 主函数 ****************
int main()
{
	//声明程序中用到的函数
	void cd_cmd(char *dir);		// cd命令处理函数
	void dir_cmd(char *dir);	// dir命令处理函数
	void GetProcessList();		// 获得系统当前进程列表
	void history_cmd();			// 获得最近输入的命令
	void add_history(char *);	// 将输入命令行添加到命令历史中
	HANDLE process(int, char[]);	// 创建进程
	BOOL killProcess(char *);	// kill进程
	void help();				// 显示帮助信息

	char c, *input, *arg[2], path[BUFSIZE];
	int input_len = 0, is_bg = 0, i, j, k;
	HANDLE hprocess;		// 进程执行结束，返回进程句柄
	DWORD dwRet;

	while (true)//显示提示符，等待用户输入命令是个无限循环过程
	{
		// 将指向输入命令的指针数组初始化
		for (i = 0; i < 2; i++)
			arg[i] = NULL;
		// 获得当前目录并存入path中，BUFSIZE是最多能够保存的路径名长度
		dwRet = GetCurrentDirectory(BUFSIZE, path);//返回目录数据实际长度存于dwRet
		if (dwRet == 0)	// 返回当前目录失败，输出出错信息
			cout << "GetCurrentDirectory failed " << GetLastError() << endl;
		else if (dwRet > BUFSIZE)// BUFSIZE长度小于返回目录数据的长度，输出出错信息
			cout << "GetCurrentDirectory failed (buffer too small; need " << dwRet << "bytes)\n";
		else
			cout << path << '>';	// 显示提示符(当前目录名+'>')

		// *********** 键盘输入 ************
		input_len = 0;
		// 将命令开头的无用字符过滤掉
		while ((c = cin.get()) == ' ' || c == '\t' || c == EOF);
		if (c == '\n')	//输入为空命令(仅输入回车符)时
			continue;	//结束本次循环，回到循环开头，重新显示提示符
		while (c != '\n')
		{
			buf[input_len++] = c;
			c = cin.get();
		}
		buf[input_len++] = '\0';	// 加上串结束符

		// 分配动态存储空间，将命令从缓存复制到input中
		input = new char[input_len];
		strcpy(input, buf);	//为了便于后边的处理，将命令行复制到input中

		// *********** 解析命令 ************
		for (i = 0, j = 0, k = 0; i < input_len && k < 2; i++)//k<2是限制只处理1个命令参数
		{										  //即arg[0]为命令，arg[1]为参数
			if (input[i] == ' ' || input[i] == '\0')
			{
				if (j == 0)		// 去掉连在一起的多个空格
					continue;
				else
				{
					buf[j++] = '\0';
					arg[k] = new char[sizeof(char)*(j + 1)];
					strcpy(arg[k++], buf);	// 将命令或参数复制到arg中
					j = 0;		// 准备取下一个参数
				}
			}
			else//不是' '和'\0'字符，则存入buf[]中
				buf[j++] = input[i];
		}
		add_history(input);	// 将输入命令添加到历史命令队列中

		// ****************** 命令处理 ******************

		if (strcmp(arg[0], "cd") == 0)	// **** cd命令 ****
		{
			if (arg[1] != NULL)
			{
				cd_cmd(arg[1]);
				delete[]arg[1];
			}
			else
				cout << "cd命令必须指定路径名!\n";
			delete[]input;
			delete[]arg[0];
			continue;	//返回循环开头，重新显示提示符
		}
		if (strcmp(arg[0], "dir") == 0)	// **** dir命令 ****
		{
			char *route;
			if (arg[1] == NULL)	// 若dir命令无参数，则对当前目录操作
			{
				route = path;		// 取当前目录
				dir_cmd(route);
			}
			else
			{
				dir_cmd(arg[1]);
				delete[]arg[1];
			}
			delete[]input;		// 释放堆空间
			delete[]arg[0];
			continue;
		}
		if (strcmp(arg[0], "tasklist") == 0)	// **** tasklist命令 ****
		{
			GetProcessList();// 该函数通过调用若干API函数，获取系统当前进程列表
			delete[]input;
			delete[]arg[0];
			if (arg[1] != NULL)//防止用户误输入命令参数
				delete arg[1];
			continue;
		}

		if (strcmp(arg[0], "fp") == 0)	// *** fp命令(前台进程) ***
		{
			if (arg[1] == NULL)
			{
				cout << "没有指定可执行文件\n";
				delete[]input;
				delete[]arg[0];
				continue;
			}
			is_bg = 0;	// 后台标志置0(不是后台进程)
			hprocess = process(is_bg, arg[1]);	//创建进程，返回新进程的句柄
			// 等待新进程执行完毕(INFINTE表示等待无限制)
			if (WaitForSingleObject(hprocess, INFINITE) == WAIT_OBJECT_0)
			{
				//如果进程执行完毕，释放控制台
				delete[]input;
				delete[]arg[0];
				delete[]arg[1];
			}
			continue;
		}

		if (strcmp(arg[0], "bg&") == 0)	// *** bg&命令(后台进程) ***
		{
			if (arg[1] == NULL)
			{
				cout << "没有指定可执行文件\n";
				delete[]input;
				delete[]arg[0];
				continue;
			}
			is_bg = 1;	// 后台标志置1(真)
			process(is_bg, arg[1]);	//为可执行文件arg[1]创建后台进程
			delete[]input;
			delete[]arg[0];
			delete[]arg[1];
			continue;
		}

		if (strcmp(arg[0], "taskkill") == 0)	// ***** kill进程 *****
		{
			BOOL success;
			if (arg[1] != NULL)
			{
				success = killProcess(arg[1]);	// arg[1]指向进程ID
				if (!success)	// 若撤销进程失败，则显示出错信息
					cout << "kill process failed!\n";
				delete[]arg[1];
			}
			else
				cout << "taskkill命令必须指定进程ID!" << endl;
			delete[]input;
			delete[]arg[0];
			if (arg[1] != NULL)//防止用户误输入命令参数
				delete arg[1];
			continue;
		}

		if (strcmp(arg[0], "history") == 0) // **** 显示历史命令 ****
		{
			history_cmd();
			delete[]input;
			delete[]arg[0];
			if (arg[1] != NULL)//防止用户误输入命令参数
				delete arg[1];
			continue;
		}

		if (strcmp(arg[0], "help") == 0)	// **** help命令 ****
		{
			help();
			delete[]input;
			delete[]arg[0];
			if (arg[1] != NULL)//防止用户误输入命令参数
				delete arg[1];
			continue;
		}

		if (strcmp(arg[0], "exit") == 0)	// **** exit命令 ****
		{
			cout << "\nBye bye!\n\n";
			delete[]input;
			delete[]arg[0];
			if (arg[1] != NULL)//防止用户误输入命令参数
				delete arg[1];
			break;		// 退出死循环，结束程序
		}

		else	// 输入命令不正确，给出出错信息
		{
			cout << "please input correct commmand!\n";
			delete[]input;
			if (arg[0])
				delete[]arg[0];
			if (arg[1])
				delete[]arg[1];
			continue;
		}
	}
}	// **** 主函数结束 ****

// ************* 相关命令出路函数 **************

void cd_cmd(char *route)	// **** cd命令实现函数 ****
{
	if (!SetCurrentDirectory(route))	//设置当前目录，若失败则返回出错信息
		cout << "SetCurrentDirectory failed " << GetLastError() << endl;
}

// ***************** dir命令实现函数 ***************** 
void dir_cmd(char *route)
{
	WIN32_FIND_DATA FindFileData;	//将找到的文件或目录以WIN32_FIND_DATA结构返回
	files_Content head, *p, *q;		//定义指定文件结构体的头结点和指针
	HANDLE hFind = INVALID_HANDLE_VALUE;	// 句柄变量初值为“非法句柄值”
	DWORD dwError;					// 定义32位整数
	char volume_name[256], str[22];
	int file = 0, dir = 0;		//文件数和目录数初始值为0
	__int64 sum_file = 0;		//总文件大小为0字节，其值较大保存为64位整数
	__int64 l_user, l_sum, l_idle;	//调用者可用空间，总容量，磁盘总可用空间
	unsigned long volume_number;	//卷序列号
	char *DirSpec[4];

	head.next = NULL;
	DirSpec[0] = new char[2];
	strncpy(DirSpec[0], route, 1);
	DirSpec[0][1] = '\0';		//DirSpec[0]为驱动器名
	DirSpec[1] = new char[4];
	strcpy(DirSpec[1], DirSpec[0]);
	strncat(DirSpec[1], ":\\", 3);	//DirSpec[1]用于获取驱动器信息
	DirSpec[2] = new char[strlen(route) + 2];
	DirSpec[3] = new char[strlen(route) + 5];
	strcpy(DirSpec[2], route);		//DirSpec[2]为dir命令的目录名
	strcpy(DirSpec[3], route);
	int len = strlen(route);
	if (route[len - 1] != '\\')
		strncat(DirSpec[2], "\\", 2);
	strncat(DirSpec[3], "\\*.*", 5);	//DirSpec[3]用于查找目录中的所有文件

	//搜素DirSpec[3]指定的文件，文件信息存于FindFileData变量中，返回找到的文件句柄
	hFind = FindFirstFile(DirSpec[3], &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)	//查找句柄返回为无效值，查找失败
		cout << "Invalid file handle, Error is " << GetLastError() << endl;
	else
	{
		//获取卷的卷名(存于volume_name)，卷序列号(存于volume_number)
		GetVolumeInformation(DirSpec[1], volume_name, 50, &volume_number, NULL, NULL, NULL, 10);
		if (strlen(volume_name) == 0)
			cout << "\n\n驱动器" << DirSpec[0] << "中的卷没有标签。" << endl;
		else
			cout << "\n\n驱动器" << DirSpec[0] << "中的卷是 " << volume_name << endl;
		cout << "卷的序列号是 " << hex << volume_number << dec << endl << endl;;
		cout << DirSpec[2] << " 的目录\n\n";
		head.time = FindFileData.ftCreationTime;//获得的文件创建时间，存入文件结构体head中
		strcpy(head.name, FindFileData.cFileName);//获得的文件名，存入文件结构体head中
		// 若数据属性是目录，则置type为0
		if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			head.type = 0;
			dir++;
		}
		else
		{
			//如果数据属性是文件，type位为1
			head.type = 1;
			head.size = FindFileData.nFileSizeLow;	//将文件大小存入结构体head中
			file++;		//文件数增1
			sum_file += FindFileData.nFileSizeLow;	//将文件大小(字节数)累加
		}
		p = &head;	// p指向头结点head

		//如果还有下一个数据，继续查找
		while (FindNextFile(hFind, &FindFileData) != 0)
		{	// 第二个结点开始，分配动态空间
			q = new files_Content[sizeof(files_Content)];
			q->next = NULL;
			q->time = FindFileData.ftCreationTime;	// 保存文件创建时间
			strcpy(q->name, FindFileData.cFileName);	// 保存文件名
			if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				q->type = 0;	// 找到的是目录
				dir++;		// 目录数增1
			}
			else	// 否则，找到的是文件
			{
				//如果数据属性是文件，type位为1
				q->type = 1;
				q->size = FindFileData.nFileSizeLow;	//将文件大小存入结构体
				file++;		//文件数增1
				sum_file += FindFileData.nFileSizeLow;	//将文件大小累加
			}
			p->next = q;	// 构成单链表
			p = q;		// p指向新结点
		}
		p->next = NULL;	// 链表尾结点的next指针须置为NULL

		//将结构体中数据的创建时间、类型、大小、名称等信息依次输出
		p = &head;	// 从链表头结点开始		
		while (p != NULL)
		{
			ftime(p->time);	// 按规定格式显示文件创建时间
			if (p->type == 0)	// 若是目录，则显示“<DOR>”
				cout << "\t<DIR>\t\t";
			else
			{	// 若是文件，则按宽度为9的格式显示文件大小(字节数)
				cout << "\t\t"; cout.width(9);
				cout << dec << (unsigned)p->size;
			}
			cout << '\t' << p->name << endl;	// 显示文件名
			p = p->next;	// 准备显示下一个目录项(文件或目录)
		}

		//显示文件和目录总数以及磁盘空间相关信息
		cout.width(15);
		cout << file << " 个文件\t\t\t";
		//printf()使用格式符“%I64d”可以输出64位整数，但“cout<<”只支持32位整数
		//故此处先将64位整数sum_file转换成以10进制形式的字符串后再输出
		_i64toa(sum_file, str, 10);	//64位整数sum_file转换成10进制字符串存于str中
		cout << str << " 字节" << endl;
		GetDiskFreeSpaceEx(DirSpec[1], (PULARGE_INTEGER)&l_user,
			(PULARGE_INTEGER)&l_sum, (PULARGE_INTEGER)&l_idle);
		cout.width(15);
		cout << dir << " 个目录\t\t\t";
		_i64toa(l_idle, str, 10);	//64位整数l_idle转换成10进制字符串存于str中
		cout << str << " 可用字节\n";
		cout.width(15);
		_i64toa(l_sum, str, 10);	//64位整数l_sum转换成10进制字符串存于str中
		cout << str << " 磁盘总字节\n\n" << endl;

		dwError = GetLastError();
		FindClose(hFind);
		// 若出现其他异常情况，则输出出错信息
		if (dwError != ERROR_NO_MORE_FILES)
			cout << "FindNextFile error. Error is " << dwError << endl;

		//释放files_Content结构体占用的动态空间
		p = &head;
		p = p->next;	// head占用的不是动态空间，跳过head
		while (p != NULL)
		{
			q = p->next;
			delete p;	// 依次释放files_Content链表的后续结点
			p = q;
		}
	}
}

// ************** tasklist命令 **************

void GetProcessList()	// 函数功能：获取系统当前运行进程列表的命令
{
	HANDLE hProcessSnap = NULL;
	PROCESSENTRY32 pe32 = { 0 };
	int pn = 0;		// 用于累计进程数
	// 对系统中的进程进行拍照
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//pid为0表示任意进出
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		cout << "\nCtreateToolhelp32Snapshot() failed:" << GetLastError();
	//使用前要填充结构大小
	pe32.dwSize = sizeof(PROCESSENTRY32);
	// 列出进程
	if (Process32First(hProcessSnap, &pe32))
	{
		DWORD dwPriorityClass;
		cout << "\n优先级\t\t进程ID\t\t线程\t\t进程名\n";
		do {
			HANDLE hProcess;
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32DefaultHeapID);
			dwPriorityClass = GetPriorityClass(hProcess);
			CloseHandle(hProcess);
			//输出结果
			cout << pe32.pcPriClassBase << "\t\t";	//输出该进程的优先级
			cout << pe32.th32ProcessID << "\t\t";	//输出该进程的pid
			cout << pe32.cntThreads << "\t\t";		//输出该进程的线程数
			cout << pe32.szExeFile << endl;		//输出进程名(或可执行文件名)
			pn++;		//进程数增1
		} while (Process32Next(hProcessSnap, &pe32));//当快照中有下一个进程，继续循环
		cout << pn << " 个进程\n" << endl;
	}
	else
		cout << "\nProcess32First() failed:" << GetLastError();
	CloseHandle(hProcessSnap);	// 释放快照句柄
}

void add_history(char *inputcmd)// ***** 将命令行插入历史队列中 *****
{
	envhis.end = (envhis.end + 1) % HISNUM;// end加1，准备将新的命令行插入队列
	// end和start指向同一数组
	if (envhis.end == envhis.start)//若队列满，则允许新插入的命令行覆盖旧命令行
		envhis.start = (envhis.start + 1) % HISNUM;	//调整队列头指针start(移一位)
	// 将命令存入end指向的数组中
	strcpy(envhis.his_cmd[envhis.end], inputcmd);
}

// ************** history 命令 ****************
void history_cmd() // 显示历史命令
{
	int i, j = 1;
	if (envhis.end == envhis.start)
		cout << "无历史命令\n";		//循环数组为空
	else if (envhis.start < envhis.end)
	{
		//显示history命令数组中start+1到end的命令
		for (i = envhis.start + 1; i <= envhis.end; i++)
		{
			cout << j << '\t' << envhis.his_cmd[i] << endl;
			j++;
		}

	}
	else//否则，应分两段处理
	{
		// 显示history命令数组中start+1到HISNUM-1的命令
		for (i = envhis.start + 1; i < HISNUM; i++)
		{
			cout << j << '\t' << envhis.his_cmd[i] << endl;
			j++;
		}
		// 显示history命令数组中0到end+1的命令
		for (i = 0; i <= envhis.end + 1; i++)
		{
			cout << j << '\t' << envhis.his_cmd[i] << endl;
			j++;
		}
	}
	cout << endl << endl;
}

// ************** 创建进程命令 ****************
HANDLE process(int bg, char appName[]) //fp和bg&命令调用此函数
{
	// 初始化进程相关信息
	STARTUPINFO si;		// 关于STARTUPINFO结构的成员的介绍，参看MSDN
	PROCESS_INFORMATION pi;	//关于PROCESS_INFORMATION结构的成员的介绍，参看MSDN

	si.cb = sizeof(si);	// si.cb的值应是STARTUPINFO结构体的大小(字节数)
	GetStartupInfo(&si);//获得STARTUPINFO结构体，存于si中	
	ZeroMemory(&pi, sizeof(pi));	// 擦去pi的内容(其内存空间清零)

	if (bg == 0)	//前台进程
	{
		//设置钩子，捕捉组合键Ctrl+C命令，收到即结束进程
		if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, TRUE) == FALSE)
		{
			cout << "Unable to install handler!\n";
			return NULL;
		}
		//用可执行文件appName创建前台进程。此函数各个参数的介绍请参看实验指导书
		CreateProcess(NULL, appName, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		return pi.hProcess;
	}
	else//创建后台进程的要点是：①新进程另开窗口；②其窗口是隐藏的
	{
		//设置进程窗口选项
		si.dwFlags = STARTF_USESHOWWINDOW;
		//若不指定此值，则将忽略下一语句的wShowWindow
		si.wShowWindow = SW_HIDE;	//隐藏窗口
		//创建后台进程，执行可执行文件appName
		CreateProcess(NULL, appName, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
		return NULL;
	}
}

// ************** taskkill命令(撤销进程) ****************
BOOL killProcess(char *pid)
{
	int id, i;
	DWORD dwExitStatus;
	HANDLE hprocess;
	id = atoi(pid);		// 将进程ID转换成整数
	hprocess = OpenProcess(PROCESS_TERMINATE, FALSE, id);//打开进程ID为id的进程，获得其句柄
	GetExitCodeProcess(hprocess, &dwExitStatus);//根据刚获得的句柄，获取其退出码存于dwExitStatus
	if (i = TerminateProcess(hprocess, dwExitStatus))//终止该进程
		return TRUE;	//若终止进程成功，返回TRUE
	else
		return FALSE;
}

// ************* 显示帮助 ***************
void help()
{
	cout << "\ncd：切换当前目录。\n";
	cout << "输入形式：cd ..\n\t  cd [drive:] [path] (cd c:\\temp)\n";
	cout << "注：cd命令以空格为分隔符区分命令和参数。\n\n";
	cout << "dir：显示目录中的文件和子目录列表。\n";
	cout << "输入形式：dir\n\t  dir [drive:] [path] (dir c:\\temp)\n";
	cout << "注：dir命令以空格为分隔符区分命令和参数。\n\n";
	cout << "tasklist：显示系统中当前进程的信息。\n";
	cout << "输入形式：tasklist\n\n";
	cout << "fp：创建进程并在前台执行。\n";
	cout << "输入形式：fp\n\n";
	cout << "bg&：创建进程并在后台执行。\n";
	cout << "输入形式：bg&\n\n";
	cout << "taskkill：终止进程。\n";
	cout << "输入形式：taskkill [pid]\n";
	cout << "注：taskkill命令以空格为分隔符，pid是进程id。\n\n";
	cout << "history：显示历史命令。\n";
	cout << "输入形式：history\n\n";
	cout << "exit：退出。\n";
	cout << "输入形式：exit\n\n\n\n";
}