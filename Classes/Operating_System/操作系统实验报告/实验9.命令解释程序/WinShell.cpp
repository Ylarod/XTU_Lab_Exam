#define _Win32_WINNT 0x0501
#include <stdlib.h>		//atoi()��
#include <iostream>
#include <windows.h>	//DWORD;HANDLE...���л������ͷ�ļ�
#include <tlhelp32.h>	//CreateToolhelp32Snapshot()
#include <string.h>
#include "WinShell.h"
using namespace std;

// ����������������������ͷ������������������治�У��ʽ�������
// ��mian()��ǰ�棬ԭ����������ǵĲ������ͷֱ���FILETIME��DWORD

// ***************** ʱ�䴦���� ******************
void ftime(FILETIME filetime)
{
	SYSTEMTIME systemtime;
	if (filetime.dwLowDateTime == -1)	// Win32ʱ��ĵ�32λ
		cout << "Never Expires\n";
	else
	{
		//��UTC(Universal Time Coordinated)�ļ�ʱ��ת���ɱ����ļ�ʱ��
		if (FileTimeToLocalFileTime(&filetime, &filetime) != 0)
		{
			//��64λʱ��ת����ϵͳʱ��
			if (FileTimeToSystemTime(&filetime, &systemtime) != 0)
			{
				//��һ���ܸ�ʽ���ʱ��
				cout.fill('0');	//����ָ���������0���
				cout << dec << systemtime.wYear << '-';
				cout.width(2); cout << systemtime.wMonth << '-';	//�·���2λ��ʾ��������
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
	cout.fill(' ');	//�ָ��ո����
}

// ************ �ص����� ************
BOOL WINAPI ConsoleHandler(DWORD CEvent)
{	// �˺�������ʲô����ϵͳ�����¼�����������Ctrl+C��
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

// **************** ������ ****************
int main()
{
	//�����������õ��ĺ���
	void cd_cmd(char *dir);		// cd�������
	void dir_cmd(char *dir);	// dir�������
	void GetProcessList();		// ���ϵͳ��ǰ�����б�
	void history_cmd();			// ���������������
	void add_history(char *);	// ��������������ӵ�������ʷ��
	HANDLE process(int, char[]);	// ��������
	BOOL killProcess(char *);	// kill����
	void help();				// ��ʾ������Ϣ

	char c, *input, *arg[2], path[BUFSIZE];
	int input_len = 0, is_bg = 0, i, j, k;
	HANDLE hprocess;		// ����ִ�н��������ؽ��̾��
	DWORD dwRet;

	while (true)//��ʾ��ʾ�����ȴ��û����������Ǹ�����ѭ������
	{
		// ��ָ�����������ָ�������ʼ��
		for (i = 0; i < 2; i++)
			arg[i] = NULL;
		// ��õ�ǰĿ¼������path�У�BUFSIZE������ܹ������·��������
		dwRet = GetCurrentDirectory(BUFSIZE, path);//����Ŀ¼����ʵ�ʳ��ȴ���dwRet
		if (dwRet == 0)	// ���ص�ǰĿ¼ʧ�ܣ����������Ϣ
			cout << "GetCurrentDirectory failed " << GetLastError() << endl;
		else if (dwRet > BUFSIZE)// BUFSIZE����С�ڷ���Ŀ¼���ݵĳ��ȣ����������Ϣ
			cout << "GetCurrentDirectory failed (buffer too small; need " << dwRet << "bytes)\n";
		else
			cout << path << '>';	// ��ʾ��ʾ��(��ǰĿ¼��+'>')

		// *********** �������� ************
		input_len = 0;
		// �����ͷ�������ַ����˵�
		while ((c = cin.get()) == ' ' || c == '\t' || c == EOF);
		if (c == '\n')	//����Ϊ������(������س���)ʱ
			continue;	//��������ѭ�����ص�ѭ����ͷ��������ʾ��ʾ��
		while (c != '\n')
		{
			buf[input_len++] = c;
			c = cin.get();
		}
		buf[input_len++] = '\0';	// ���ϴ�������

		// ���䶯̬�洢�ռ䣬������ӻ��渴�Ƶ�input��
		input = new char[input_len];
		strcpy(input, buf);	//Ϊ�˱��ں�ߵĴ����������и��Ƶ�input��

		// *********** �������� ************
		for (i = 0, j = 0, k = 0; i < input_len && k < 2; i++)//k<2������ֻ����1���������
		{										  //��arg[0]Ϊ���arg[1]Ϊ����
			if (input[i] == ' ' || input[i] == '\0')
			{
				if (j == 0)		// ȥ������һ��Ķ���ո�
					continue;
				else
				{
					buf[j++] = '\0';
					arg[k] = new char[sizeof(char)*(j + 1)];
					strcpy(arg[k++], buf);	// �������������Ƶ�arg��
					j = 0;		// ׼��ȡ��һ������
				}
			}
			else//����' '��'\0'�ַ��������buf[]��
				buf[j++] = input[i];
		}
		add_history(input);	// ������������ӵ���ʷ���������

		// ****************** ����� ******************

		if (strcmp(arg[0], "cd") == 0)	// **** cd���� ****
		{
			if (arg[1] != NULL)
			{
				cd_cmd(arg[1]);
				delete[]arg[1];
			}
			else
				cout << "cd�������ָ��·����!\n";
			delete[]input;
			delete[]arg[0];
			continue;	//����ѭ����ͷ��������ʾ��ʾ��
		}
		if (strcmp(arg[0], "dir") == 0)	// **** dir���� ****
		{
			char *route;
			if (arg[1] == NULL)	// ��dir�����޲�������Ե�ǰĿ¼����
			{
				route = path;		// ȡ��ǰĿ¼
				dir_cmd(route);
			}
			else
			{
				dir_cmd(arg[1]);
				delete[]arg[1];
			}
			delete[]input;		// �ͷŶѿռ�
			delete[]arg[0];
			continue;
		}
		if (strcmp(arg[0], "tasklist") == 0)	// **** tasklist���� ****
		{
			GetProcessList();// �ú���ͨ����������API��������ȡϵͳ��ǰ�����б�
			delete[]input;
			delete[]arg[0];
			if (arg[1] != NULL)//��ֹ�û��������������
				delete arg[1];
			continue;
		}

		if (strcmp(arg[0], "fp") == 0)	// *** fp����(ǰ̨����) ***
		{
			if (arg[1] == NULL)
			{
				cout << "û��ָ����ִ���ļ�\n";
				delete[]input;
				delete[]arg[0];
				continue;
			}
			is_bg = 0;	// ��̨��־��0(���Ǻ�̨����)
			hprocess = process(is_bg, arg[1]);	//�������̣������½��̵ľ��
			// �ȴ��½���ִ�����(INFINTE��ʾ�ȴ�������)
			if (WaitForSingleObject(hprocess, INFINITE) == WAIT_OBJECT_0)
			{
				//�������ִ����ϣ��ͷſ���̨
				delete[]input;
				delete[]arg[0];
				delete[]arg[1];
			}
			continue;
		}

		if (strcmp(arg[0], "bg&") == 0)	// *** bg&����(��̨����) ***
		{
			if (arg[1] == NULL)
			{
				cout << "û��ָ����ִ���ļ�\n";
				delete[]input;
				delete[]arg[0];
				continue;
			}
			is_bg = 1;	// ��̨��־��1(��)
			process(is_bg, arg[1]);	//Ϊ��ִ���ļ�arg[1]������̨����
			delete[]input;
			delete[]arg[0];
			delete[]arg[1];
			continue;
		}

		if (strcmp(arg[0], "taskkill") == 0)	// ***** kill���� *****
		{
			BOOL success;
			if (arg[1] != NULL)
			{
				success = killProcess(arg[1]);	// arg[1]ָ�����ID
				if (!success)	// ����������ʧ�ܣ�����ʾ������Ϣ
					cout << "kill process failed!\n";
				delete[]arg[1];
			}
			else
				cout << "taskkill�������ָ������ID!" << endl;
			delete[]input;
			delete[]arg[0];
			if (arg[1] != NULL)//��ֹ�û��������������
				delete arg[1];
			continue;
		}

		if (strcmp(arg[0], "history") == 0) // **** ��ʾ��ʷ���� ****
		{
			history_cmd();
			delete[]input;
			delete[]arg[0];
			if (arg[1] != NULL)//��ֹ�û��������������
				delete arg[1];
			continue;
		}

		if (strcmp(arg[0], "help") == 0)	// **** help���� ****
		{
			help();
			delete[]input;
			delete[]arg[0];
			if (arg[1] != NULL)//��ֹ�û��������������
				delete arg[1];
			continue;
		}

		if (strcmp(arg[0], "exit") == 0)	// **** exit���� ****
		{
			cout << "\nBye bye!\n\n";
			delete[]input;
			delete[]arg[0];
			if (arg[1] != NULL)//��ֹ�û��������������
				delete arg[1];
			break;		// �˳���ѭ������������
		}

		else	// ���������ȷ������������Ϣ
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
}	// **** ���������� ****

// ************* ��������·���� **************

void cd_cmd(char *route)	// **** cd����ʵ�ֺ��� ****
{
	if (!SetCurrentDirectory(route))	//���õ�ǰĿ¼����ʧ���򷵻س�����Ϣ
		cout << "SetCurrentDirectory failed " << GetLastError() << endl;
}

// ***************** dir����ʵ�ֺ��� ***************** 
void dir_cmd(char *route)
{
	WIN32_FIND_DATA FindFileData;	//���ҵ����ļ���Ŀ¼��WIN32_FIND_DATA�ṹ����
	files_Content head, *p, *q;		//����ָ���ļ��ṹ���ͷ����ָ��
	HANDLE hFind = INVALID_HANDLE_VALUE;	// ���������ֵΪ���Ƿ����ֵ��
	DWORD dwError;					// ����32λ����
	char volume_name[256], str[22];
	int file = 0, dir = 0;		//�ļ�����Ŀ¼����ʼֵΪ0
	__int64 sum_file = 0;		//���ļ���СΪ0�ֽڣ���ֵ�ϴ󱣴�Ϊ64λ����
	__int64 l_user, l_sum, l_idle;	//�����߿��ÿռ䣬�������������ܿ��ÿռ�
	unsigned long volume_number;	//�����к�
	char *DirSpec[4];

	head.next = NULL;
	DirSpec[0] = new char[2];
	strncpy(DirSpec[0], route, 1);
	DirSpec[0][1] = '\0';		//DirSpec[0]Ϊ��������
	DirSpec[1] = new char[4];
	strcpy(DirSpec[1], DirSpec[0]);
	strncat(DirSpec[1], ":\\", 3);	//DirSpec[1]���ڻ�ȡ��������Ϣ
	DirSpec[2] = new char[strlen(route) + 2];
	DirSpec[3] = new char[strlen(route) + 5];
	strcpy(DirSpec[2], route);		//DirSpec[2]Ϊdir�����Ŀ¼��
	strcpy(DirSpec[3], route);
	int len = strlen(route);
	if (route[len - 1] != '\\')
		strncat(DirSpec[2], "\\", 2);
	strncat(DirSpec[3], "\\*.*", 5);	//DirSpec[3]���ڲ���Ŀ¼�е������ļ�

	//����DirSpec[3]ָ�����ļ����ļ���Ϣ����FindFileData�����У������ҵ����ļ����
	hFind = FindFirstFile(DirSpec[3], &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)	//���Ҿ������Ϊ��Чֵ������ʧ��
		cout << "Invalid file handle, Error is " << GetLastError() << endl;
	else
	{
		//��ȡ��ľ���(����volume_name)�������к�(����volume_number)
		GetVolumeInformation(DirSpec[1], volume_name, 50, &volume_number, NULL, NULL, NULL, 10);
		if (strlen(volume_name) == 0)
			cout << "\n\n������" << DirSpec[0] << "�еľ�û�б�ǩ��" << endl;
		else
			cout << "\n\n������" << DirSpec[0] << "�еľ��� " << volume_name << endl;
		cout << "������к��� " << hex << volume_number << dec << endl << endl;;
		cout << DirSpec[2] << " ��Ŀ¼\n\n";
		head.time = FindFileData.ftCreationTime;//��õ��ļ�����ʱ�䣬�����ļ��ṹ��head��
		strcpy(head.name, FindFileData.cFileName);//��õ��ļ����������ļ��ṹ��head��
		// ������������Ŀ¼������typeΪ0
		if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			head.type = 0;
			dir++;
		}
		else
		{
			//��������������ļ���typeλΪ1
			head.type = 1;
			head.size = FindFileData.nFileSizeLow;	//���ļ���С����ṹ��head��
			file++;		//�ļ�����1
			sum_file += FindFileData.nFileSizeLow;	//���ļ���С(�ֽ���)�ۼ�
		}
		p = &head;	// pָ��ͷ���head

		//���������һ�����ݣ���������
		while (FindNextFile(hFind, &FindFileData) != 0)
		{	// �ڶ�����㿪ʼ�����䶯̬�ռ�
			q = new files_Content[sizeof(files_Content)];
			q->next = NULL;
			q->time = FindFileData.ftCreationTime;	// �����ļ�����ʱ��
			strcpy(q->name, FindFileData.cFileName);	// �����ļ���
			if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				q->type = 0;	// �ҵ�����Ŀ¼
				dir++;		// Ŀ¼����1
			}
			else	// �����ҵ������ļ�
			{
				//��������������ļ���typeλΪ1
				q->type = 1;
				q->size = FindFileData.nFileSizeLow;	//���ļ���С����ṹ��
				file++;		//�ļ�����1
				sum_file += FindFileData.nFileSizeLow;	//���ļ���С�ۼ�
			}
			p->next = q;	// ���ɵ�����
			p = q;		// pָ���½��
		}
		p->next = NULL;	// ����β����nextָ������ΪNULL

		//���ṹ�������ݵĴ���ʱ�䡢���͡���С�����Ƶ���Ϣ�������
		p = &head;	// ������ͷ��㿪ʼ		
		while (p != NULL)
		{
			ftime(p->time);	// ���涨��ʽ��ʾ�ļ�����ʱ��
			if (p->type == 0)	// ����Ŀ¼������ʾ��<DOR>��
				cout << "\t<DIR>\t\t";
			else
			{	// �����ļ����򰴿��Ϊ9�ĸ�ʽ��ʾ�ļ���С(�ֽ���)
				cout << "\t\t"; cout.width(9);
				cout << dec << (unsigned)p->size;
			}
			cout << '\t' << p->name << endl;	// ��ʾ�ļ���
			p = p->next;	// ׼����ʾ��һ��Ŀ¼��(�ļ���Ŀ¼)
		}

		//��ʾ�ļ���Ŀ¼�����Լ����̿ռ������Ϣ
		cout.width(15);
		cout << file << " ���ļ�\t\t\t";
		//printf()ʹ�ø�ʽ����%I64d���������64λ����������cout<<��ֻ֧��32λ����
		//�ʴ˴��Ƚ�64λ����sum_fileת������10������ʽ���ַ����������
		_i64toa(sum_file, str, 10);	//64λ����sum_fileת����10�����ַ�������str��
		cout << str << " �ֽ�" << endl;
		GetDiskFreeSpaceEx(DirSpec[1], (PULARGE_INTEGER)&l_user,
			(PULARGE_INTEGER)&l_sum, (PULARGE_INTEGER)&l_idle);
		cout.width(15);
		cout << dir << " ��Ŀ¼\t\t\t";
		_i64toa(l_idle, str, 10);	//64λ����l_idleת����10�����ַ�������str��
		cout << str << " �����ֽ�\n";
		cout.width(15);
		_i64toa(l_sum, str, 10);	//64λ����l_sumת����10�����ַ�������str��
		cout << str << " �������ֽ�\n\n" << endl;

		dwError = GetLastError();
		FindClose(hFind);
		// �����������쳣����������������Ϣ
		if (dwError != ERROR_NO_MORE_FILES)
			cout << "FindNextFile error. Error is " << dwError << endl;

		//�ͷ�files_Content�ṹ��ռ�õĶ�̬�ռ�
		p = &head;
		p = p->next;	// headռ�õĲ��Ƕ�̬�ռ䣬����head
		while (p != NULL)
		{
			q = p->next;
			delete p;	// �����ͷ�files_Content����ĺ������
			p = q;
		}
	}
}

// ************** tasklist���� **************

void GetProcessList()	// �������ܣ���ȡϵͳ��ǰ���н����б������
{
	HANDLE hProcessSnap = NULL;
	PROCESSENTRY32 pe32 = { 0 };
	int pn = 0;		// �����ۼƽ�����
	// ��ϵͳ�еĽ��̽�������
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//pidΪ0��ʾ�������
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		cout << "\nCtreateToolhelp32Snapshot() failed:" << GetLastError();
	//ʹ��ǰҪ���ṹ��С
	pe32.dwSize = sizeof(PROCESSENTRY32);
	// �г�����
	if (Process32First(hProcessSnap, &pe32))
	{
		DWORD dwPriorityClass;
		cout << "\n���ȼ�\t\t����ID\t\t�߳�\t\t������\n";
		do {
			HANDLE hProcess;
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32DefaultHeapID);
			dwPriorityClass = GetPriorityClass(hProcess);
			CloseHandle(hProcess);
			//������
			cout << pe32.pcPriClassBase << "\t\t";	//����ý��̵����ȼ�
			cout << pe32.th32ProcessID << "\t\t";	//����ý��̵�pid
			cout << pe32.cntThreads << "\t\t";		//����ý��̵��߳���
			cout << pe32.szExeFile << endl;		//���������(���ִ���ļ���)
			pn++;		//��������1
		} while (Process32Next(hProcessSnap, &pe32));//������������һ�����̣�����ѭ��
		cout << pn << " ������\n" << endl;
	}
	else
		cout << "\nProcess32First() failed:" << GetLastError();
	CloseHandle(hProcessSnap);	// �ͷſ��վ��
}

void add_history(char *inputcmd)// ***** �������в�����ʷ������ *****
{
	envhis.end = (envhis.end + 1) % HISNUM;// end��1��׼�����µ������в������
	// end��startָ��ͬһ����
	if (envhis.end == envhis.start)//�����������������²���������и��Ǿ�������
		envhis.start = (envhis.start + 1) % HISNUM;	//��������ͷָ��start(��һλ)
	// ���������endָ���������
	strcpy(envhis.his_cmd[envhis.end], inputcmd);
}

// ************** history ���� ****************
void history_cmd() // ��ʾ��ʷ����
{
	int i, j = 1;
	if (envhis.end == envhis.start)
		cout << "����ʷ����\n";		//ѭ������Ϊ��
	else if (envhis.start < envhis.end)
	{
		//��ʾhistory����������start+1��end������
		for (i = envhis.start + 1; i <= envhis.end; i++)
		{
			cout << j << '\t' << envhis.his_cmd[i] << endl;
			j++;
		}

	}
	else//����Ӧ�����δ���
	{
		// ��ʾhistory����������start+1��HISNUM-1������
		for (i = envhis.start + 1; i < HISNUM; i++)
		{
			cout << j << '\t' << envhis.his_cmd[i] << endl;
			j++;
		}
		// ��ʾhistory����������0��end+1������
		for (i = 0; i <= envhis.end + 1; i++)
		{
			cout << j << '\t' << envhis.his_cmd[i] << endl;
			j++;
		}
	}
	cout << endl << endl;
}

// ************** ������������ ****************
HANDLE process(int bg, char appName[]) //fp��bg&������ô˺���
{
	// ��ʼ�����������Ϣ
	STARTUPINFO si;		// ����STARTUPINFO�ṹ�ĳ�Ա�Ľ��ܣ��ο�MSDN
	PROCESS_INFORMATION pi;	//����PROCESS_INFORMATION�ṹ�ĳ�Ա�Ľ��ܣ��ο�MSDN

	si.cb = sizeof(si);	// si.cb��ֵӦ��STARTUPINFO�ṹ��Ĵ�С(�ֽ���)
	GetStartupInfo(&si);//���STARTUPINFO�ṹ�壬����si��	
	ZeroMemory(&pi, sizeof(pi));	// ��ȥpi������(���ڴ�ռ�����)

	if (bg == 0)	//ǰ̨����
	{
		//���ù��ӣ���׽��ϼ�Ctrl+C����յ�����������
		if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, TRUE) == FALSE)
		{
			cout << "Unable to install handler!\n";
			return NULL;
		}
		//�ÿ�ִ���ļ�appName����ǰ̨���̡��˺������������Ľ�����ο�ʵ��ָ����
		CreateProcess(NULL, appName, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		return pi.hProcess;
	}
	else//������̨���̵�Ҫ���ǣ����½��������ڣ����䴰�������ص�
	{
		//���ý��̴���ѡ��
		si.dwFlags = STARTF_USESHOWWINDOW;
		//����ָ����ֵ���򽫺�����һ����wShowWindow
		si.wShowWindow = SW_HIDE;	//���ش���
		//������̨���̣�ִ�п�ִ���ļ�appName
		CreateProcess(NULL, appName, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
		return NULL;
	}
}

// ************** taskkill����(��������) ****************
BOOL killProcess(char *pid)
{
	int id, i;
	DWORD dwExitStatus;
	HANDLE hprocess;
	id = atoi(pid);		// ������IDת��������
	hprocess = OpenProcess(PROCESS_TERMINATE, FALSE, id);//�򿪽���IDΪid�Ľ��̣��������
	GetExitCodeProcess(hprocess, &dwExitStatus);//���ݸջ�õľ������ȡ���˳������dwExitStatus
	if (i = TerminateProcess(hprocess, dwExitStatus))//��ֹ�ý���
		return TRUE;	//����ֹ���̳ɹ�������TRUE
	else
		return FALSE;
}

// ************* ��ʾ���� ***************
void help()
{
	cout << "\ncd���л���ǰĿ¼��\n";
	cout << "������ʽ��cd ..\n\t  cd [drive:] [path] (cd c:\\temp)\n";
	cout << "ע��cd�����Կո�Ϊ�ָ�����������Ͳ�����\n\n";
	cout << "dir����ʾĿ¼�е��ļ�����Ŀ¼�б�\n";
	cout << "������ʽ��dir\n\t  dir [drive:] [path] (dir c:\\temp)\n";
	cout << "ע��dir�����Կո�Ϊ�ָ�����������Ͳ�����\n\n";
	cout << "tasklist����ʾϵͳ�е�ǰ���̵���Ϣ��\n";
	cout << "������ʽ��tasklist\n\n";
	cout << "fp���������̲���ǰִ̨�С�\n";
	cout << "������ʽ��fp\n\n";
	cout << "bg&���������̲��ں�ִ̨�С�\n";
	cout << "������ʽ��bg&\n\n";
	cout << "taskkill����ֹ���̡�\n";
	cout << "������ʽ��taskkill [pid]\n";
	cout << "ע��taskkill�����Կո�Ϊ�ָ�����pid�ǽ���id��\n\n";
	cout << "history����ʾ��ʷ���\n";
	cout << "������ʽ��history\n\n";
	cout << "exit���˳���\n";
	cout << "������ʽ��exit\n\n\n\n";
}