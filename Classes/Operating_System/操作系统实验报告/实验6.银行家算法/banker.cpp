#include <iostream>
using namespace std;
class Banker {
	int *Allocation;	// 分配矩阵
	int *Need;			// 尚需矩阵
	int *Available;		// 可用资源向量
	int *squeue;			// 安全序列
	int	safe;			// safe=1,存在安全序列
public:
	int m, n;			// m为资源种类数，n为进程数
	Banker(int, int);	// 构造函数
	~Banker();			// 析构函数
	bool Ifsafe();		// 安全性检查函数
	int banker(int k, int *Request);	// 银行家算法
	void Print();		// 输出资源分配情况
	void Getmn(int &, int &);	// 获取资源种类数m和进程数n
};

Banker::Banker(int m0, int n0)	// 构造函数
{
	int i, j;
	m = m0; n = n0; safe = 0;
	Allocation = new int[n*m];
	Need = new int[n*m];
	Available = new int[m];
	squeue = new int[n];

	cout << "输入分配矩阵Allocation：\n";
	for (i = 0; i < n; i++)
	{
		cout << "输入分配矩阵的第 " << i + 1 << " 行：";
		for (j = 0; j < m; j++)
			cin >> Allocation[i*m + j];
	}
	cout << "\n输入尚需矩阵Need：\n";
	for (i = 0; i < n; i++)
	{
		cout << "输入尚需矩阵的第 " << i + 1 << " 行：";
		for (j = 0; j < m; j++)
			cin >> Need[i*m + j];
	}
	cout << "\n输入可用资源向量Available：";
	for (i = 0; i < m; i++)
		cin >> Available[i];
}

Banker::~Banker()
{
	delete[]Allocation;	// 释放分配矩阵空间
	delete[]Need;			// 释放尚需矩阵空间
	delete[]Available;		// 释放可用资源向量
	delete[]squeue;			// 释放安全序列空间
}

// 判断系统状态是否安全。Finish:标志；Work:工作向量。
bool Banker::Ifsafe()
{
	int *Work = new int[m];	// 定义工作向量
	int *Finish = new int[n];	// 定义标志数组
	int i, j, flag, k = 0;
	for (i = 0; i < n; i++)
		Finish[i] = 0;		// 置未标记标志
	for (j = 0; j < m; j++)
		Work[j] = Available[j];
	do {
		flag = 0;
		for (i = 0; i < n; i++)
		{
			if (Finish[i] == 0)
			{
				for (j = 0; j < m; j++)	// 判断Need[i]是否不超过Work
					if (Need[i*m + j] > Work[j]) break;
				if (j == m) {			// 若Pi的需求Need[i]≤当前可用资源能Work
					Finish[i] = 1;	// 置Pi能完成的标志
					flag = 1;			// 为了继续循环(查找)
					squeue[k++] = i;	// 顺便记下安全序列
					for (j = 0; j < m; j++)//Pi完成后，它所占用的资源归入Work中
						Work[j] += Allocation[i*m + j];
				}
			}
		}
	} while (flag);

	delete[]Work;
	for (i = 0; i < n; i++)
		if (Finish[i] == 0)	// 若有进程未完成，则系统状态不安全
		{
			delete[]Finish;
			return false;	// 返回“不安全”
		}
	delete[]Finish;
	return true;			// 返回“安全”
}

// 银行家算法。k:进程序号; Request:该进程的请求向量
int Banker::banker(int k, int *Request)
{
	int i;
	for (i = 0; i < m; i++)
		if (Request[i] > Need[k*m + i])
		{
			cout << "\nError : Request of P" << k << " > Max[" << k << "]\n";
			return 0;
		}
	for (i = 0; i < m; i++)
		if (Request[i] > Available[i])
		{
			cout << "\nRequest > Available,P" << k << " is blocked\n";
			return 0;
		}
	for (i = 0; i < m; i++)		// 系统试探分配资源
	{
		Available[i] -= Request[i];
		Allocation[k*m + i] += Request[i];
		Need[k*m + i] -= Request[i];
	}
	safe = Ifsafe();			// 判断是否安全
	if (safe)		// 若系统状态仍是安全的
	{
		cout << "\n满足进程P" << k << "的请求(";
		for (i = 0; i < m - 1; i++)
			cout << Request[i] << ',';
		cout << Request[i] << ")后，系统状态仍然是安全的。安全序列为：\n";
		for (i = 0; i < n - 1; i++)
			cout << 'P' << squeue[i] << ',';
		cout << 'P' << squeue[i] << endl;
	}
	else			// 若系统状态已是不安全
	{
		cout << "\n如果满足进程P" << k << "的资源请求(";
		for (i = 0; i < m - 1; i++)
			cout << Request[i] << ',';
		cout << Request[i] << ")，系统将进入不安全状态，" << endl;
		cout << "故系统将拒绝该进程的请求。" << endl;
		for (i = 0; i < m; i++)	// 将试探分配作废
		{
			Available[i] += Request[i];
			Allocation[k*m + i] -= Request[i];
			Need[k*m + i] += Request[i];
		}
	}
	return safe;
}

void Banker::Print()		// 输出当前系统的资源分配情况
{
	int i, j;
	cout << "\n Allocation	    Need	 Available\n\n";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			cout.width(3);
			cout << Allocation[i*m + j];
		}
		cout << '\t';
		for (j = 0; j < m; j++)
		{
			cout.width(3);
			cout << Need[i*m + j];
		}
		if (i == 0)
		{
			cout << "\t";
			for (j = 0; j < m; j++)
			{
				cout.width(3);
				cout << Available[j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

void Banker::Getmn(int &x, int &y)
{
	x = m;
	y = n;
}

int main()
{
	int i, stat;
	int k, m, n;			// m,n分别是资源种类数和进程数
	Banker b(3, 5);		// 定义对象b，其资源种类数和进程数分别为3和5
	b.Getmn(m, n);
	int *Request = new int[m];    // 进程申请资源向量
	b.Print();			// 显示当前资源分配情况
	stat = b.Ifsafe();	// 判断T0时刻状态是否安全
	if (stat)
		cout << "当前系统状态是安全的" << endl;
	else {
		cout << "当前系统状态是不安全的" << endl;
		delete[]Request;
		return 0;
	}
	while (1)			// 当输入的进程号出错时，循环结束
	{
		cout << "\n请输入进程号 (0--" << n - 1 << ", -1=Exit) : ";
		cin >> k;
		if (k >= n)
		{
			cout << "\nError : The number of Process is out of range !" << endl;
			continue;
		}
		if (k < 0) break;
		cout << "请输入进程P" << k << "申请的资源数: ";
		for (i = 0; i < m; i++)
			cin >> Request[i];
		stat = b.banker(k, Request);
		b.Print();
	}
	delete[]Request;
	return 1;
}