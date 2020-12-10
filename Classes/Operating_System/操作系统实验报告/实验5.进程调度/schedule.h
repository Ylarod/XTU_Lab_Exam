#include <string.h>
#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;
#ifndef SCHEDULE_H
#define SCHEDULE_H

enum STATUS { RUN, READY, WAIT };	// 进程的三种状态列表

typedef struct PCB	// 进程控制块
{
	int id;				// 进程标识PID
	char name[20];		// 进程名
	enum STATUS status;	// 进程状态：RUN, READY, WAIT
	int flag;	//为了不重复显示，额外增加此成员
	HANDLE hThis;		// 进程句柄
	DWORD threadID;		// 线程ID
	int count;			// 进程计划运行时间长度，以时间片为单位
	struct PCB* next;	// 指向就绪队列或缓冲区(空闲PCB)链的指针
} PCB, * pPCB;
// 就绪队列或空白PCB队列的管理用的结构
typedef struct
{
	pPCB head;			// 队首指针
	pPCB tail;			// 队尾指针
	int pcbNum;			// 队列中的进程数
} readyList, freeList, * pList;


// 进程控制块数为30(最多允许创建30个进程)
const int PCB_LIMIT = 30;

HANDLE init();
void createProcess(char* name, int ax);
void scheduleProcess();
void removeProcess(char* name);
void fprintReadyList();
void printReadyList();
void printCurrent();
void stopAllThreads();
#endif