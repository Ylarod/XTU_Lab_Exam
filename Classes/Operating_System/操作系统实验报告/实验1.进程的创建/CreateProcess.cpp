#include <bits/stdc++.h>
#include <windows.h>	//Win32 API
#define MAX_LINE_LEN 128
void NewProc(char*);	// ��������
using namespace std;
char cmdline[MAX_LINE_LEN];
int main()
{
	char ch;
	ifstream fid;
	HWND hWindow;
	hWindow=GetForegroundWindow();//��ȡ���������д��ڵľ��
	//�ı䱾�������д��ڵ�λ�úʹ�Сʹ֮���ӽ��̴�����������
	MoveWindow(hWindow,10,10,425,320,TRUE);
	fid.open("cmdline.txt");//�򿪴洢�����е��ļ�
	if (!fid)	//���ļ������ڣ�����
	{
		cout<<"Can't open cmdline.txt !"<<endl;
		ch=cin.get();
		exit(0);
	}
	//���ļ��������������У����ڴ�������
	while (fid.getline(cmdline,MAX_LINE_LEN)) {
		cout<<"cmdline="<<cmdline<<endl;//�������������
		NewProc(cmdline);//�����½���
	}
	cout<<"\nEnd"<<endl;
	return 0;
}
void NewProc(char* cmdline)
{
	static int counter=1;
	STARTUPINFO si={sizeof(STARTUPINFO)};
	//ʹ��ԱdwX,dwY��dwXSize,dwYSize��Ч
	//Ŀ����Ϊ���ܵ��������̴���λ�úʹ�С
	si.dwFlags=STARTF_USEPOSITION|STARTF_USESIZE;
	si.dwXSize=400;	//���ڿ�
	si.dwYSize=260;	//���ڸ�
	PROCESS_INFORMATION pi;
	DWORD dwx=10,dwy=10;	//�������Ͻ�λ��
	switch (counter%4)
	{
	case 0 : si.dwX=dwx;	//ָ�����ĸ��ӽ��̵Ĵ��ڵ����Ͻ�λ��
			 si.dwY=dwy;
			 break;
	case 1 : si.dwX=dwx+425;//ָ����һ���ӽ��̵Ĵ��ڵ����Ͻ�λ��
			 si.dwY=dwy;
			 break;
	case 2 : si.dwX=dwx;	//ָ���ڶ����ӽ��̵Ĵ��ڵ����Ͻ�λ��
			 si.dwY=dwy+310;
			 break;
	case 3 : si.dwX=dwx+425;//ָ���������ӽ��̵Ĵ��ڵ����Ͻ�λ��
			 si.dwY=dwy+310;
			 break;
	}
	counter++;
	BOOL result=CreateProcess(
		NULL,			//ûָ����ִ��ģ����
		cmdline,		//·���Ϳ�ִ��ģ����
		NULL,			//�ӽ��̲��ܼ̳д˺������صľ��
		NULL,			//�ӽ��̵��̲߳��ܼ̳д˺������صľ��
		FALSE,			//�½��̲��ܴӵ��ô˺������̼̳д˾��
		NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,
						//����һ��û����������������ͨ���̡������´���
		NULL,			//�½���ʹ�õ��ô˺�������(������)�Ļ�����
		NULL,			//�½���ʹ�ø����̵ĵ�ǰĿ¼��Ϊ�Լ��ĵ�ǰĿ¼
		&si,			//STARTUPINFO�ṹ�����½�����������γ���(��ʾ)
		&pi		//PROCESS_INFORMATION�ṹ���ڽ����½��̵ı�ʶ��Ϣ
		);
	//��ʾ��ϸ�Ĵ������̳�����Ϣ
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
		//����������ָʾ����(����Ϣ��FormatMessage������lpMsgBuf��)
		MessageBox(NULL,(LPSTR)lpMsgBuf,"Error",MB_OK | MB_ICONINFORMATION);
		LocalFree(lpMsgBuf);
		//�ͷ���FormatMessage�ж�̬����Ŀռ�
	}
}
