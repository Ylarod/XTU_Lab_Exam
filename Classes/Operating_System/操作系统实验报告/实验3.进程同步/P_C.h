// ********** P_C.h **********
#include <iostream>
#include <windows.h>
#include <time.h>		// time( )

using namespace std; 

//缓冲区结构
typedef struct Buffer {
	DWORD data;		//数据
	int Number;		//线程序号
} *lpBuffer;
// 生产者线程的工作代码
DWORD WINAPI ProducerThread(LPVOID p);
// 消费者线程的工作代码
DWORD WINAPI ConsumerThread(LPVOID p);
// 描述生产者-消费者的类
class sy_pc {
private:
	int in;		//生产者使用的循环缓冲区的下标
	int out;	//消费者使用的循环缓冲区的下标
	int bcount;	//循环缓冲区的个数
	HANDLE empty;	//指向生产者的私有信号量
	HANDLE full;	//指向消费者的私有信号量
	HANDLE mutex;	//指示互斥信号量
	lpBuffer buffer;	//指向一个循环缓冲区
public:
	sy_pc(int);		//构造函数
	int getbuffer(lpBuffer);	//从缓冲区取出一个"产品"
	int putbuffer(Buffer);		//向缓冲区放入一个"产品"
	~sy_pc();					//析构函数
};

sy_pc::sy_pc(int c) 	//构造函数
{
	in=0;		//生产者对循环缓冲操作的初始位置
	out=0;		//生产者对循环缓冲操作的初始位置
	bcount=c;	//缓冲区的个数为c
	empty=CreateSemaphore(NULL,bcount,bcount,"sempty");
	full=CreateSemaphore(NULL,0,bcount,"sfull");
	mutex=CreateSemaphore(NULL,1,1,"smutex");
	buffer=new Buffer[bcount];	//循环缓冲是个顺序队列(数组)
}

int sy_pc::getbuffer(lpBuffer Buf)	//取到的产品由参数Buf带回
{
	WaitForSingleObject(full,INFINITE);		//先对私有信号量执行wait
	WaitForSingleObject(mutex,INFINITE);	//再对公用信号量(互斥信号量)指向wait
	*Buf=buffer[out];		//在out所指位置取出一个产品
	out=(out+1)%bcount;		//out循环增1
	ReleaseSemaphore(mutex,1,NULL);	//mutex的count增1
	ReleaseSemaphore(empty,1,NULL);	//empty的count增1
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

sy_pc::~sy_pc() //析构函数
{
	delete []buffer;
}

