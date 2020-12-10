// ����ͬ����������-����������
#include "P_C.h"

#define M 5			//������5��������
#define N 3			//������3��������
CRITICAL_SECTION cs_Screen;	//����߳̾�����Ļ��������ٽ������Ʊ���
sy_pc s_pc(10);				//����ȫ�ֶ��󣬼򻯲������ݷ�ʽ

int main()	//������(���߳�ִ�еĴ���)
{
	HANDLE hThread[100];// ������ഴ��100���߳�
	int i,j,sum;
	DWORD ExitCode;
	InitializeCriticalSection(&cs_Screen); 	//��ʼ���ٽ�������cs_Screen
	srand((unsigned int)time(NULL));	// ʹ�õ�ǰʱ��Ϊ������е�"����"
	for (i=1,j=0;i<=M;i++,j++)	//����5���������߳�
	{						//ÿ���������߳�ִ��ProducerThread( )�Ĵ���
		hThread[j]=CreateThread(NULL,0,ProducerThread, (LPVOID)&i,0,NULL);
		Sleep(10);
	}
	for (i=1;i<=N;i++,j++)	//����3���������߳�
	{					//ÿ���������߳�ִ��ConsumerThread ( )�Ĵ���
		hThread[j]=CreateThread(NULL,0,ConsumerThread, (LPVOID)&i,0,NULL);
		Sleep(10);
	}
	while (true)//���̲߳���ѭ����ֱ���������߳̽���
	{
		EnterCriticalSection(&cs_Screen); //׼�������ٽ���
		cout<<"���߳��������� ***********************"<<endl;
		LeaveCriticalSection(&cs_Screen);	// �˳��ٽ���
		Sleep(1000);
		for (i=0,sum=0;i<j;i++)//�ܹ���j�����߳�
		{
			ExitCode=0;
			GetExitCodeThread(hThread[i],&ExitCode);//��ȡ���̵߳��˳���
			if (ExitCode==1)	//������߳��ѽ�������ͳ����sum
				sum=sum+ExitCode;
		}
		if (sum==j)	//���������߳��Ѿ������������߳�Ҳ����
			break;
	}
	cout<<"�������߳��Ѿ����������߳�Ҳ������ ************"<<endl;
	return 0; 
}
// �������̹߳�������
DWORD WINAPI ProducerThread(LPVOID p)
{
	int *ip=(int*)p;		//ת��Ϊ����ָ��
	int ThreadNumber=*ip;	//ȡ����ָ����ָ������ֵ
	int naptime,in;
	Buffer b;			//����һ������������b
	for (int i=1;i<=3*N;i++)//ÿ�������߹�����9����Ʒ���뻺����
	{
		b.data=rand();		//b��data��Ա���������ʾ
		b.Number=ThreadNumber;	//b��Number��Աֵ���ϲ����̵߳����
		in=s_pc.putbuffer(b);	//��b���뻺���������ص�ǰ���±�in��ֵ
		EnterCriticalSection(&cs_Screen); //׼�������ٽ���
		cout<<"Producer "<<ThreadNumber<<" �򻺳���Ͷ���˵� "
			<<i<<" ������ "<<b.data<<"��in="<<in<<endl;
		LeaveCriticalSection(&cs_Screen);	// �˳��ٽ���
		naptime=100+rand()%200; 	//˯��100~300ms
		Sleep(naptime);
	}
	EnterCriticalSection(&cs_Screen); //׼�������ٽ���
	cout<<"Producer "<<ThreadNumber<<" �������"<<endl;
	LeaveCriticalSection(&cs_Screen);	// �˳��ٽ���
	return 1;		//���̵߳ķ���ֵ(�˳���)Ϊ1
}
// �������̹߳�������
DWORD WINAPI ConsumerThread(LPVOID p)
{
	int ThreadNumber=*((int*)p);
	int naptime,out;
	Buffer b;
	for (int i=1;i<=3*M;i++)//ÿ�������߹���ȡ15����Ʒ�����
	{
		out=s_pc.getbuffer(&b);//�ӻ�����ȡ��Ʒ����b�У������±�out
		EnterCriticalSection(&cs_Screen); //׼�������ٽ���
		cout<<"Consumer "<<ThreadNumber<<" �ӻ�����ȡ���˵� "
			<<i<<" ������ "<<b.data;
		cout<<", ����Producer "<<b.Number<<"��ŵġ�out="<<out<<endl;
		LeaveCriticalSection(&cs_Screen);	// �˳��ٽ���
		naptime=100+rand()%200;
		Sleep(naptime);	//˯�ߵȴ�һ��ʱ��ֻ��Ϊ����ʾ
	}
	EnterCriticalSection(&cs_Screen); //׼�������ٽ���
	cout<<"Consumer "<<ThreadNumber<<" �������"<<endl;
	LeaveCriticalSection(&cs_Screen);	// �˳��ٽ���
	return 1; 		//���̵߳ķ���ֵ(�˳���)Ϊ1
}

