// ************* Mult-Thread *************
#include <windows.h>	//API
#include <time.h>		//rand()用
#include <iostream>
#include <conio.h>		//_getch()

using namespace std;

//设立一个全局开关，在规定时刻(新创建线程生命期结束时刻)通知它们
int runFlag=true;
//各线程所要执行的模块
DWORD WINAPI  threadwork(LPVOID ThreadNo);

CRITICAL_SECTION cs_Screen;	//因多线程竞争屏幕，故设此临界区控制变量

//主函数main，也是本进程的主线程执行的代码
int main(void)
{
	WORD wRunTime;		// 线程的生命周期(秒)，WORD是32位有符号整型，即int
	SYSTEMTIME now;		// 时间结构(时、分、秒)
	DWORD ThreadID[100];	// 线程id，假设最多创建100个线程
	HANDLE hThread[100];	// 线程句柄
	int iThread;		// 创建的线程数
	int ctime;			// 当前时间(时、分、秒)折合成的秒数
	int etime;			// 新线程结束时间(时、分、秒)折合成的秒数
	int bhour;			// 新线程开始执行时间的小时数
	int chour;			// 当前时间的小时数
	int temp;			// 暂存变量
	char ch;

	InitializeCriticalSection(&cs_Screen);	//初始化临界区控制变量

	srand((unsigned int)time(NULL));	// 使用当前时间为随机序列的"种子"

	//输入新线程数iThread和新线程运行的时间wRunTime，为了便于观
	//察程序的输出结果，建议线程数和线程运行时间一般都不要超过5
	cout<<"请输入要创建的新线程数：";
	cin>>iThread;
	cout<<"新线程运行的时间(秒数)：";
	cin>>wRunTime;

	//计算线程的生命期(结束时间)，所有新线程共用
	GetSystemTime(&now);	//调用返回格林威治时间，存于now
	if (now.wHour>16)
		now.wHour -= 16;	//转化为北京时间
	else
		now.wHour += 8;
	bhour=now.wHour;		//记下开始的小时值
	temp=now.wHour*3600+now.wMinute*60+now.wSecond;	//把当前时间化成秒数
	etime=temp+wRunTime;	//线程结束的秒数

	//循环创建新线程，数量有参数指定
	cout.fill('0');
	cout.width(2); cout<<"新线程开始时间："<<now.wHour<<':';
	cout.width(2); cout<<now.wMinute<<':';
	cout.width(2); cout<<now.wSecond<<"(主线程输出信息)"<<endl;
	
	for (int i=0; i<iThread; i++) {
		/* 线程函数的参数类型必须是LPVOID(即void *)，故用
		  强制类型转换运算符(LPVOID)将整型i转换成LPVOID */
		hThread[i]=CreateThread(NULL,0,threadwork, (LPVOID)i,0,&ThreadID[i]);
		Sleep(100);		// 主线程让出时间，使新建的线程运行
	}

	// 在子线程工作时不断循环，判断这些线程生命是否到期
	while (runFlag)
	{
		EnterCriticalSection(&cs_Screen); //准备进入临界区
		cout<<"************ 主线程正在运行 ………… "<<endl;
		LeaveCriticalSection(&cs_Screen);	// 退出临界区
		GetSystemTime(&now);
		if (now.wHour>16)
			now.wHour -= 16;	//转化为北京时间
		else
			now.wHour += 8;
		if (now.wHour<bhour)	//处理时间过"00::00"的情况
			chour=now.wHour+24;
		else
			chour=now.wHour;
		ctime=chour*3600+now.wMinute*60+now.wSecond; //当前时间的秒数
		if (ctime>=etime)		//若已到新线程结束时间
		{
			runFlag = FALSE;
			EnterCriticalSection(&cs_Screen); //准备进入临界区
			cout.width(2); cout<<"新线程结束时间："<<now.wHour<<':';
			cout.width(2); cout<<now.wMinute<<':';
			cout.width(2); cout<<now.wSecond<<"(主线程输出信息)"<<endl;
			LeaveCriticalSection(&cs_Screen);	// 退出临界区
		}
		Sleep(1000);	//主线程睡眠100ms
	}

	//在整个进程(主线程)结束前留出一段时间好让各子线程完成自己
	//的工作(也便于我们从它们结束前的输出来观察线程同步问题)
	Sleep(2000);

	GetSystemTime(&now);
	if (now.wHour>16)
		now.wHour -= 16;	//转化为北京时间
	else
		now.wHour += 8;
	//由于子线程已经结束，屏幕显示不再需要互斥
	cout.width(2); cout<<"主线程结束时间："<<now.wHour<<':';
	cout.width(2); cout<<now.wMinute<<':';
	cout.width(2); cout<<now.wSecond<<"(主线程输出信息)"<<endl;
	cout.fill(' ');

	ch=_getch();	//为便于观察程序不在开发环境运行的输出结果
	
	return 0;
}

//每个新线程执行的代码
DWORD WINAPI threadwork(LPVOID ThreadNO)		//LPVOID即(void *)
{
	int napTime;		//睡眠时间(毫秒)
	int iThreadNO=(int)ThreadNO;	// 线程编号
	int count=0;

	//提示创建的相应线程已经启动
	EnterCriticalSection(&cs_Screen); //准备进入临界区
	cout.width(2);
	cout<<"Thread "<<iThreadNO<<" 开始运行。"<<endl;
	LeaveCriticalSection(&cs_Screen);	// 退出临界区

	//以下线程用于使线程睡眠一段时间(让出CPU共其它线程动
	//作，并保证主线程能更及时获得CPU以改变runFlag标志)
	while (runFlag)
	{
		napTime=100+rand()%200;	//子线程睡眠时间在100~300ms之间
		count++;
		EnterCriticalSection(&cs_Screen); //准备进入临界区
		cout<<"Thread "<<iThreadNO<<" 第";
		cout.width(2);cout<<count<<" 次被调度运行 …… ";
		cout<<"(====== 这是线程 "<<iThreadNO<<" 输出的信息 ======)"<<endl;
		LeaveCriticalSection(&cs_Screen);	// 退出临界区
		Sleep(napTime);	//睡眠一随机时间更能观察线程并发执行情况
	}

	EnterCriticalSection(&cs_Screen); //准备进入临界区
	cout<<"###### Thread "<<iThreadNO<<" 结束 ######"<<endl;
	LeaveCriticalSection(&cs_Screen);	// 退出临界区

	return (DWORD)iThreadNO;
}

