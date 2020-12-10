// 进程同步：生产者-消费者问题
#include "P_C.h"

#define M 5			//假设有5个生产者
#define N 3			//假设有3个消费者
CRITICAL_SECTION cs_Screen;	//因多线程竞争屏幕，故设此临界区控制变量
sy_pc s_pc(10);				//定义全局对象，简化参数传递方式

int main()	//主函数(主线程执行的代码)
{
	HANDLE hThread[100];// 假设最多创建100个线程
	int i,j,sum;
	DWORD ExitCode;
	InitializeCriticalSection(&cs_Screen); 	//初始化临界区对象cs_Screen
	srand((unsigned int)time(NULL));	// 使用当前时间为随机序列的"种子"
	for (i=1,j=0;i<=M;i++,j++)	//创建5个生产者线程
	{						//每个生产者线程执行ProducerThread( )的代码
		hThread[j]=CreateThread(NULL,0,ProducerThread, (LPVOID)&i,0,NULL);
		Sleep(10);
	}
	for (i=1;i<=N;i++,j++)	//创建3个消费者线程
	{					//每个消费者线程执行ConsumerThread ( )的代码
		hThread[j]=CreateThread(NULL,0,ConsumerThread, (LPVOID)&i,0,NULL);
		Sleep(10);
	}
	while (true)//主线程不断循环，直到所有子线程结束
	{
		EnterCriticalSection(&cs_Screen); //准备进入临界区
		cout<<"主线程正在运行 ***********************"<<endl;
		LeaveCriticalSection(&cs_Screen);	// 退出临界区
		Sleep(1000);
		for (i=0,sum=0;i<j;i++)//总共有j个子线程
		{
			ExitCode=0;
			GetExitCodeThread(hThread[i],&ExitCode);//获取子线程的退出码
			if (ExitCode==1)	//如果该线程已结束，则统计入sum
				sum=sum+ExitCode;
		}
		if (sum==j)	//若所有子线程已经结束，则主线程也结束
			break;
	}
	cout<<"所有子线程已经结束，主线程也将结束 ************"<<endl;
	return 0; 
}
// 生产者线程工作代码
DWORD WINAPI ProducerThread(LPVOID p)
{
	int *ip=(int*)p;		//转化为整型指针
	int ThreadNumber=*ip;	//取整型指针所指变量的值
	int naptime,in;
	Buffer b;			//定义一个缓冲区变量b
	for (int i=1;i<=3*N;i++)//每个生产者共生产9个产品放入缓冲区
	{
		b.data=rand();		//b的data成员用随机数演示
		b.Number=ThreadNumber;	//b的Number成员值是上缠着线程的序号
		in=s_pc.putbuffer(b);	//将b放入缓冲区，返回当前的下标in的值
		EnterCriticalSection(&cs_Screen); //准备进入临界区
		cout<<"Producer "<<ThreadNumber<<" 向缓冲区投放了第 "
			<<i<<" 个数据 "<<b.data<<"。in="<<in<<endl;
		LeaveCriticalSection(&cs_Screen);	// 退出临界区
		naptime=100+rand()%200; 	//睡眠100~300ms
		Sleep(naptime);
	}
	EnterCriticalSection(&cs_Screen); //准备进入临界区
	cout<<"Producer "<<ThreadNumber<<" 运行完毕"<<endl;
	LeaveCriticalSection(&cs_Screen);	// 退出临界区
	return 1;		//子线程的返回值(退出码)为1
}
// 消费者线程工作代码
DWORD WINAPI ConsumerThread(LPVOID p)
{
	int ThreadNumber=*((int*)p);
	int naptime,out;
	Buffer b;
	for (int i=1;i<=3*M;i++)//每个消费者共获取15个产品后结束
	{
		out=s_pc.getbuffer(&b);//从缓冲区取产品放在b中，返回下标out
		EnterCriticalSection(&cs_Screen); //准备进入临界区
		cout<<"Consumer "<<ThreadNumber<<" 从缓冲区取得了第 "
			<<i<<" 个数据 "<<b.data;
		cout<<", 它是Producer "<<b.Number<<"存放的。out="<<out<<endl;
		LeaveCriticalSection(&cs_Screen);	// 退出临界区
		naptime=100+rand()%200;
		Sleep(naptime);	//睡眠等待一段时间只是为了演示
	}
	EnterCriticalSection(&cs_Screen); //准备进入临界区
	cout<<"Consumer "<<ThreadNumber<<" 运行完毕"<<endl;
	LeaveCriticalSection(&cs_Screen);	// 退出临界区
	return 1; 		//子线程的返回值(退出码)为1
}

