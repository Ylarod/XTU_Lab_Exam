// ********** P_C.h **********
#include <iostream>
#include <windows.h>
#include <time.h>		// time( )

using namespace std; 

//�������ṹ
typedef struct Buffer {
	DWORD data;		//����
	int Number;		//�߳����
} *lpBuffer;
// �������̵߳Ĺ�������
DWORD WINAPI ProducerThread(LPVOID p);
// �������̵߳Ĺ�������
DWORD WINAPI ConsumerThread(LPVOID p);
// ����������-�����ߵ���
class sy_pc {
private:
	int in;		//������ʹ�õ�ѭ�����������±�
	int out;	//������ʹ�õ�ѭ�����������±�
	int bcount;	//ѭ���������ĸ���
	HANDLE empty;	//ָ�������ߵ�˽���ź���
	HANDLE full;	//ָ�������ߵ�˽���ź���
	HANDLE mutex;	//ָʾ�����ź���
	lpBuffer buffer;	//ָ��һ��ѭ��������
public:
	sy_pc(int);		//���캯��
	int getbuffer(lpBuffer);	//�ӻ�����ȡ��һ��"��Ʒ"
	int putbuffer(Buffer);		//�򻺳�������һ��"��Ʒ"
	~sy_pc();					//��������
};

sy_pc::sy_pc(int c) 	//���캯��
{
	in=0;		//�����߶�ѭ����������ĳ�ʼλ��
	out=0;		//�����߶�ѭ����������ĳ�ʼλ��
	bcount=c;	//�������ĸ���Ϊc
	empty=CreateSemaphore(NULL,bcount,bcount,"sempty");
	full=CreateSemaphore(NULL,0,bcount,"sfull");
	mutex=CreateSemaphore(NULL,1,1,"smutex");
	buffer=new Buffer[bcount];	//ѭ�������Ǹ�˳�����(����)
}

int sy_pc::getbuffer(lpBuffer Buf)	//ȡ���Ĳ�Ʒ�ɲ���Buf����
{
	WaitForSingleObject(full,INFINITE);		//�ȶ�˽���ź���ִ��wait
	WaitForSingleObject(mutex,INFINITE);	//�ٶԹ����ź���(�����ź���)ָ��wait
	*Buf=buffer[out];		//��out��ָλ��ȡ��һ����Ʒ
	out=(out+1)%bcount;		//outѭ����1
	ReleaseSemaphore(mutex,1,NULL);	//mutex��count��1
	ReleaseSemaphore(empty,1,NULL);	//empty��count��1
	return out;
}

int sy_pc::putbuffer(Buffer b)
{
	WaitForSingleObject(empty,INFINITE);
	WaitForSingleObject(mutex,INFINITE);
	buffer[in]=b;
	in=(in+1)%bcount;
	ReleaseSemaphore(mutex,1,NULL);
	ReleaseSemaphore(full,1,NULL);
	return in;
}

sy_pc::~sy_pc() //��������
{
	delete []buffer;
}

