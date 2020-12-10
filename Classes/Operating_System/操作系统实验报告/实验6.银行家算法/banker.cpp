#include <iostream>
using namespace std;
class Banker {
	int *Allocation;	// �������
	int *Need;			// �������
	int *Available;		// ������Դ����
	int *squeue;			// ��ȫ����
	int	safe;			// safe=1,���ڰ�ȫ����
public:
	int m, n;			// mΪ��Դ��������nΪ������
	Banker(int, int);	// ���캯��
	~Banker();			// ��������
	bool Ifsafe();		// ��ȫ�Լ�麯��
	int banker(int k, int *Request);	// ���м��㷨
	void Print();		// �����Դ�������
	void Getmn(int &, int &);	// ��ȡ��Դ������m�ͽ�����n
};

Banker::Banker(int m0, int n0)	// ���캯��
{
	int i, j;
	m = m0; n = n0; safe = 0;
	Allocation = new int[n*m];
	Need = new int[n*m];
	Available = new int[m];
	squeue = new int[n];

	cout << "����������Allocation��\n";
	for (i = 0; i < n; i++)
	{
		cout << "����������ĵ� " << i + 1 << " �У�";
		for (j = 0; j < m; j++)
			cin >> Allocation[i*m + j];
	}
	cout << "\n�����������Need��\n";
	for (i = 0; i < n; i++)
	{
		cout << "�����������ĵ� " << i + 1 << " �У�";
		for (j = 0; j < m; j++)
			cin >> Need[i*m + j];
	}
	cout << "\n���������Դ����Available��";
	for (i = 0; i < m; i++)
		cin >> Available[i];
}

Banker::~Banker()
{
	delete[]Allocation;	// �ͷŷ������ռ�
	delete[]Need;			// �ͷ��������ռ�
	delete[]Available;		// �ͷſ�����Դ����
	delete[]squeue;			// �ͷŰ�ȫ���пռ�
}

// �ж�ϵͳ״̬�Ƿ�ȫ��Finish:��־��Work:����������
bool Banker::Ifsafe()
{
	int *Work = new int[m];	// ���幤������
	int *Finish = new int[n];	// �����־����
	int i, j, flag, k = 0;
	for (i = 0; i < n; i++)
		Finish[i] = 0;		// ��δ��Ǳ�־
	for (j = 0; j < m; j++)
		Work[j] = Available[j];
	do {
		flag = 0;
		for (i = 0; i < n; i++)
		{
			if (Finish[i] == 0)
			{
				for (j = 0; j < m; j++)	// �ж�Need[i]�Ƿ񲻳���Work
					if (Need[i*m + j] > Work[j]) break;
				if (j == m) {			// ��Pi������Need[i]�ܵ�ǰ������Դ��Work
					Finish[i] = 1;	// ��Pi����ɵı�־
					flag = 1;			// Ϊ�˼���ѭ��(����)
					squeue[k++] = i;	// ˳����°�ȫ����
					for (j = 0; j < m; j++)//Pi��ɺ�����ռ�õ���Դ����Work��
						Work[j] += Allocation[i*m + j];
				}
			}
		}
	} while (flag);

	delete[]Work;
	for (i = 0; i < n; i++)
		if (Finish[i] == 0)	// ���н���δ��ɣ���ϵͳ״̬����ȫ
		{
			delete[]Finish;
			return false;	// ���ء�����ȫ��
		}
	delete[]Finish;
	return true;			// ���ء���ȫ��
}

// ���м��㷨��k:�������; Request:�ý��̵���������
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
	for (i = 0; i < m; i++)		// ϵͳ��̽������Դ
	{
		Available[i] -= Request[i];
		Allocation[k*m + i] += Request[i];
		Need[k*m + i] -= Request[i];
	}
	safe = Ifsafe();			// �ж��Ƿ�ȫ
	if (safe)		// ��ϵͳ״̬���ǰ�ȫ��
	{
		cout << "\n�������P" << k << "������(";
		for (i = 0; i < m - 1; i++)
			cout << Request[i] << ',';
		cout << Request[i] << ")��ϵͳ״̬��Ȼ�ǰ�ȫ�ġ���ȫ����Ϊ��\n";
		for (i = 0; i < n - 1; i++)
			cout << 'P' << squeue[i] << ',';
		cout << 'P' << squeue[i] << endl;
	}
	else			// ��ϵͳ״̬���ǲ���ȫ
	{
		cout << "\n����������P" << k << "����Դ����(";
		for (i = 0; i < m - 1; i++)
			cout << Request[i] << ',';
		cout << Request[i] << ")��ϵͳ�����벻��ȫ״̬��" << endl;
		cout << "��ϵͳ���ܾ��ý��̵�����" << endl;
		for (i = 0; i < m; i++)	// ����̽��������
		{
			Available[i] += Request[i];
			Allocation[k*m + i] -= Request[i];
			Need[k*m + i] += Request[i];
		}
	}
	return safe;
}

void Banker::Print()		// �����ǰϵͳ����Դ�������
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
	int k, m, n;			// m,n�ֱ�����Դ�������ͽ�����
	Banker b(3, 5);		// �������b������Դ�������ͽ������ֱ�Ϊ3��5
	b.Getmn(m, n);
	int *Request = new int[m];    // ����������Դ����
	b.Print();			// ��ʾ��ǰ��Դ�������
	stat = b.Ifsafe();	// �ж�T0ʱ��״̬�Ƿ�ȫ
	if (stat)
		cout << "��ǰϵͳ״̬�ǰ�ȫ��" << endl;
	else {
		cout << "��ǰϵͳ״̬�ǲ���ȫ��" << endl;
		delete[]Request;
		return 0;
	}
	while (1)			// ������Ľ��̺ų���ʱ��ѭ������
	{
		cout << "\n��������̺� (0--" << n - 1 << ", -1=Exit) : ";
		cin >> k;
		if (k >= n)
		{
			cout << "\nError : The number of Process is out of range !" << endl;
			continue;
		}
		if (k < 0) break;
		cout << "���������P" << k << "�������Դ��: ";
		for (i = 0; i < m; i++)
			cin >> Request[i];
		stat = b.banker(k, Request);
		b.Print();
	}
	delete[]Request;
	return 1;
}