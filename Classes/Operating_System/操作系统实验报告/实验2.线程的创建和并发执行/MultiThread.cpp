// ************* Mult-Thread *************
#include <windows.h>	//API
#include <time.h>		//rand()��
#include <iostream>
#include <conio.h>		//_getch()

using namespace std;

//����һ��ȫ�ֿ��أ��ڹ涨ʱ��(�´����߳������ڽ���ʱ��)֪ͨ����
int runFlag=true;
//���߳���Ҫִ�е�ģ��
DWORD WINAPI  threadwork(LPVOID ThreadNo);

CRITICAL_SECTION cs_Screen;	//����߳̾�����Ļ��������ٽ������Ʊ���

//������main��Ҳ�Ǳ����̵����߳�ִ�еĴ���
int main(void)
{
	WORD wRunTime;		// �̵߳���������(��)��WORD��32λ�з������ͣ���int
	SYSTEMTIME now;		// ʱ��ṹ(ʱ���֡���)
	DWORD ThreadID[100];	// �߳�id��������ഴ��100���߳�
	HANDLE hThread[100];	// �߳̾��
	int iThread;		// �������߳���
	int ctime;			// ��ǰʱ��(ʱ���֡���)�ۺϳɵ�����
	int etime;			// ���߳̽���ʱ��(ʱ���֡���)�ۺϳɵ�����
	int bhour;			// ���߳̿�ʼִ��ʱ���Сʱ��
	int chour;			// ��ǰʱ���Сʱ��
	int temp;			// �ݴ����
	char ch;

	InitializeCriticalSection(&cs_Screen);	//��ʼ���ٽ������Ʊ���

	srand((unsigned int)time(NULL));	// ʹ�õ�ǰʱ��Ϊ������е�"����"

	//�������߳���iThread�����߳����е�ʱ��wRunTime��Ϊ�˱��ڹ�
	//�������������������߳������߳�����ʱ��һ�㶼��Ҫ����5
	cout<<"������Ҫ���������߳�����";
	cin>>iThread;
	cout<<"���߳����е�ʱ��(����)��";
	cin>>wRunTime;

	//�����̵߳�������(����ʱ��)���������̹߳���
	GetSystemTime(&now);	//���÷��ظ�������ʱ�䣬����now
	if (now.wHour>16)
		now.wHour -= 16;	//ת��Ϊ����ʱ��
	else
		now.wHour += 8;
	bhour=now.wHour;		//���¿�ʼ��Сʱֵ
	temp=now.wHour*3600+now.wMinute*60+now.wSecond;	//�ѵ�ǰʱ�仯������
	etime=temp+wRunTime;	//�߳̽���������

	//ѭ���������̣߳������в���ָ��
	cout.fill('0');
	cout.width(2); cout<<"���߳̿�ʼʱ�䣺"<<now.wHour<<':';
	cout.width(2); cout<<now.wMinute<<':';
	cout.width(2); cout<<now.wSecond<<"(���߳������Ϣ)"<<endl;
	
	for (int i=0; i<iThread; i++) {
		/* �̺߳����Ĳ������ͱ�����LPVOID(��void *)������
		  ǿ������ת�������(LPVOID)������iת����LPVOID */
		hThread[i]=CreateThread(NULL,0,threadwork, (LPVOID)i,0,&ThreadID[i]);
		Sleep(100);		// ���߳��ó�ʱ�䣬ʹ�½����߳�����
	}

	// �����̹߳���ʱ����ѭ�����ж���Щ�߳������Ƿ���
	while (runFlag)
	{
		EnterCriticalSection(&cs_Screen); //׼�������ٽ���
		cout<<"************ ���߳��������� �������� "<<endl;
		LeaveCriticalSection(&cs_Screen);	// �˳��ٽ���
		GetSystemTime(&now);
		if (now.wHour>16)
			now.wHour -= 16;	//ת��Ϊ����ʱ��
		else
			now.wHour += 8;
		if (now.wHour<bhour)	//����ʱ���"00::00"�����
			chour=now.wHour+24;
		else
			chour=now.wHour;
		ctime=chour*3600+now.wMinute*60+now.wSecond; //��ǰʱ�������
		if (ctime>=etime)		//���ѵ����߳̽���ʱ��
		{
			runFlag = FALSE;
			EnterCriticalSection(&cs_Screen); //׼�������ٽ���
			cout.width(2); cout<<"���߳̽���ʱ�䣺"<<now.wHour<<':';
			cout.width(2); cout<<now.wMinute<<':';
			cout.width(2); cout<<now.wSecond<<"(���߳������Ϣ)"<<endl;
			LeaveCriticalSection(&cs_Screen);	// �˳��ٽ���
		}
		Sleep(1000);	//���߳�˯��100ms
	}

	//����������(���߳�)����ǰ����һ��ʱ����ø����߳�����Լ�
	//�Ĺ���(Ҳ�������Ǵ����ǽ���ǰ��������۲��߳�ͬ������)
	Sleep(2000);

	GetSystemTime(&now);
	if (now.wHour>16)
		now.wHour -= 16;	//ת��Ϊ����ʱ��
	else
		now.wHour += 8;
	//�������߳��Ѿ���������Ļ��ʾ������Ҫ����
	cout.width(2); cout<<"���߳̽���ʱ�䣺"<<now.wHour<<':';
	cout.width(2); cout<<now.wMinute<<':';
	cout.width(2); cout<<now.wSecond<<"(���߳������Ϣ)"<<endl;
	cout.fill(' ');

	ch=_getch();	//Ϊ���ڹ۲�����ڿ����������е�������
	
	return 0;
}

//ÿ�����߳�ִ�еĴ���
DWORD WINAPI threadwork(LPVOID ThreadNO)		//LPVOID��(void *)
{
	int napTime;		//˯��ʱ��(����)
	int iThreadNO=(int)ThreadNO;	// �̱߳��
	int count=0;

	//��ʾ��������Ӧ�߳��Ѿ�����
	EnterCriticalSection(&cs_Screen); //׼�������ٽ���
	cout.width(2);
	cout<<"Thread "<<iThreadNO<<" ��ʼ���С�"<<endl;
	LeaveCriticalSection(&cs_Screen);	// �˳��ٽ���

	//�����߳�����ʹ�߳�˯��һ��ʱ��(�ó�CPU�������̶߳�
	//��������֤���߳��ܸ���ʱ���CPU�Ըı�runFlag��־)
	while (runFlag)
	{
		napTime=100+rand()%200;	//���߳�˯��ʱ����100~300ms֮��
		count++;
		EnterCriticalSection(&cs_Screen); //׼�������ٽ���
		cout<<"Thread "<<iThreadNO<<" ��";
		cout.width(2);cout<<count<<" �α��������� ���� ";
		cout<<"(====== �����߳� "<<iThreadNO<<" �������Ϣ ======)"<<endl;
		LeaveCriticalSection(&cs_Screen);	// �˳��ٽ���
		Sleep(napTime);	//˯��һ���ʱ����ܹ۲��̲߳���ִ�����
	}

	EnterCriticalSection(&cs_Screen); //׼�������ٽ���
	cout<<"###### Thread "<<iThreadNO<<" ���� ######"<<endl;
	LeaveCriticalSection(&cs_Screen);	// �˳��ٽ���

	return (DWORD)iThreadNO;
}

