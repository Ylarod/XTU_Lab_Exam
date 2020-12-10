#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

struct pagetable	//页表结构
{
	int sflag;		//状态标志，"1"表示该页在内存
	int framenum;	//内存块号
	int aflag;		//访问标志，"1"表示该页已被访问过
	int mflag;		//修改标志，"1"表示该页已被修改过
};
pagetable *ptab;	// 指向页表的指针

int psize = 4096;		// 页的大小为4K字节
int PN;				// 进程的页数
int BN;				// 分配给该进程的内存块数
//int MB=65536;		// 假设内存共有65536个块
int *ps;			// 指向页号的FIFO队列的指针

void Printptab()	//输出(显示)页表
{
	cout << "页号\t状态\t块号\t访问位\t修改位" << endl;
	for (int i = 0; i < PN; i++)
	{
		cout << ' ' << i << "\t ";
		cout << ptab[i].sflag << "\t ";
		cout << ptab[i].framenum << "\t ";
		cout << ptab[i].aflag << '\t';
		cout << ptab[i].mflag << endl;
	}
}

void FIFO(int vaddr, int &k)	//FIFO页面置换函数
{
	int b;					// 内存块号
	int pn;					// 当前要访问的页号
	int pp;					// 将被淘汰的页号
	int offset;				// 页内偏移
	unsigned int paddr;		// 物理地址
	int mf;					// 修稿标志

	mf = vaddr % 2;				// 参数vaddr的最低位兼作修改标志
	pn = vaddr / psize;
	offset = vaddr % psize;

	pp = ps[k];				// 取出将要被淘汰的页号
	b = ptab[pp].framenum;// 取出被淘汰页所在的内存块号
	if (ptab[pp].mflag == 1)
		cout << "被置换的" << pp << "号页存盘后淘汰,";
	else
		cout << "被置换的" << pp << "号页直接被淘汰,";
	// 修改页表
	ptab[pp].sflag = 0;		// 置pp页已不在内存的标志
	ptab[pp].framenum = 0;	// 操作系统实际上不作此置0工作
	ptab[pp].aflag = 0;		// 此处置0只是为了显示页表清楚
	ptab[pp].mflag = 0;		// 此处置0只是为了显示页表清楚
	ptab[pn].sflag = 1;		// pn页调入内存
	ptab[pn].framenum = b;
	ptab[pn].aflag = 1;
	ptab[pn].mflag = mf;

	ps[k] = pn;				// 页号入队
	k = (k + 1) % BN;			// 调整循环队列ps的指针

	paddr = b * psize + offset;	/*形成物理地址*/
	cout << "虚地址" << vaddr << "所在的" << pn << "页调入" << b
		<< "块中,对应实地址是" << paddr << endl;		//输出绝对地址
}

bool response(int vaddr, int &n)
{
	static int k = 0;			// FIFO页号循环队列中，k所指的页是将被淘汰的页
	static int bn = 0;		// 已分配给该进程的内存块数
	int b, bb;				// b是申请得到的内存块号
	int pn;					// 当前要访问的页号
	int offset;				// 页内偏移
	unsigned int paddr;		// 物理地址
	int mf;					// 修改标志

	mf = vaddr % 2;				// 参数vaddr的最低位兼作修改标志
	pn = vaddr / psize;
	offset = vaddr % psize;

	if (pn >= PN)				// 地址越界
	{
		cout << "虚地址" << vaddr << "所在的页号为" << pn << "发生地址越界错误!" << endl;
		return false;
	}

	if (ptab[pn].sflag == 1)	// 所访问的页已在内存
	{
		cout << "虚地址" << vaddr << "所在的" << pn << "页已经在内存的"
			<< ptab[pn].framenum << "块中，其对应的物理地址为 ";
		paddr = ptab[pn].framenum*psize + offset;
		cout << paddr << endl;
		if (ptab[pn].mflag == 0 && mf == 1)
			ptab[pn].mflag = mf;	// 修改页表中修改标志位
	}
	else		// 产生缺页中断
	{
		if (bn < BN)			// 尚有内存块可分配
		{
			bb = rand();
			b = bb * 2 + bb % 2;	// 假设内存块号不超过0x7fff * 2（即65535）
			ps[bn] = pn;		// 页号入队
			bn++;			// 已分配给该进程的内存块数增1

			// 修改页表
			ptab[pn].sflag = 1;
			ptab[pn].framenum = b;
			ptab[pn].aflag = 1;
			ptab[pn].mflag = mf;

			paddr = b * psize + offset;	// 计算对应的物理地址(重定位)

			cout << "虚地址" << vaddr << "所在的" << pn << "页调入内存的" << b << "块中，";
			cout << "其对应的物理地址为 " << paddr << endl;
		}
		else		// 缺页中断中发生页面置换
		{
			n++;	// 页面置换次数增1
			FIFO(vaddr, k);	// 采用FIFO页面置换算法
		}
	}	// 缺页中断完成
	cout << "页号队列：";
	for (int i = 0; i < BN; i++)
		cout << ps[i] << ' ';
	cout << endl;
	return true;
}

void init()	// 初始化
{
	int i;
	ps = new int[BN];			// 分配FIFO页号队列空间
	for (i = 0; i < BN; i++)
		ps[i] = -1;			// 初始化页号队列为空
	ptab = new pagetable[PN];	// 分配页表空间
	for (i = 0; i < PN; i++)		// 初始化页表
	{
		ptab[i].sflag = 0;
		ptab[i].mflag = 0;
		ptab[i].aflag = 0;
		ptab[i].framenum = 0;
	}
}

int main()
{
	int *pqueue;		// 指向页面引用串的指针	
	int L;				// 该进程的页面引用串的长度
	int nn = 0;			// 用于统计页面置换次数
	int i, vaddr, vd, pn;
	bool flag;

	srand((unsigned int)time(NULL));	// 置随机序列的“种子”(使用当前时间为种子)

	cout << "请输入进程的页数：";
	cin >> PN;
	cout << "请输入分配给该进程的内存块数：";
	cin >> BN;
	cout << "请输入该进程的页面引用串的长度：";
	cin >> L;
	cout << endl;

	init();	// 初始化

	pqueue = new int[L];		// 分配页面引用串空间
	for (i = 0; i < L; i++)
		pqueue[i] = -1;		// 初始化页面引用串

	for (i = 0; i < L; i++)
	{
		vd = rand();			//访问串中页号由随机数模拟
		vaddr = vd * PN / 8;		//rand()生成的随机数不超过0x7fff，相当于8页，需折合成PN页。
//		vaddr=vd*(PN+1)/8;	//rand()生成的随机数不超过0x7fff，相当于8页，需折合成PN页。
							//PN+1是为了使之可能产生“地址越界“”
		pn = vaddr / psize;		// 计算出页号
		pqueue[i] = pn;		// 该页号存入页面引用串中
		flag = response(vaddr, nn);
		if (!flag)			//若发生地址越界，则结束程序
		{
			L = i + 1;			//记下已访问的页数
			break;
		}
		Sleep(3000 + (rand() % 5) * 2000);
	}

	cout << "\n页面引用串为：";
	for (i = 0; i < L - 1; i++)
		cout << pqueue[i] << ',';
	cout << pqueue[i] << endl;
	cout << "页面置换次数为 " << nn << endl;

	cout << "\n最终页表变为(不在内存的页对应的内存块号和修改标志无效)：" << endl;
	Printptab();	//输出页表

	delete[]ps;
	delete[]ptab;
	delete[]pqueue;
}