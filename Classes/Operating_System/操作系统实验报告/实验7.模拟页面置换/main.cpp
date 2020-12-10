#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

struct pagetable	//ҳ��ṹ
{
	int sflag;		//״̬��־��"1"��ʾ��ҳ���ڴ�
	int framenum;	//�ڴ���
	int aflag;		//���ʱ�־��"1"��ʾ��ҳ�ѱ����ʹ�
	int mflag;		//�޸ı�־��"1"��ʾ��ҳ�ѱ��޸Ĺ�
};
pagetable *ptab;	// ָ��ҳ���ָ��

int psize = 4096;		// ҳ�Ĵ�СΪ4K�ֽ�
int PN;				// ���̵�ҳ��
int BN;				// ������ý��̵��ڴ����
//int MB=65536;		// �����ڴ湲��65536����
int *ps;			// ָ��ҳ�ŵ�FIFO���е�ָ��

void Printptab()	//���(��ʾ)ҳ��
{
	cout << "ҳ��\t״̬\t���\t����λ\t�޸�λ" << endl;
	for (int i = 0; i < PN; i++)
	{
		cout << ' ' << i << "\t ";
		cout << ptab[i].sflag << "\t ";
		cout << ptab[i].framenum << "\t ";
		cout << ptab[i].aflag << '\t';
		cout << ptab[i].mflag << endl;
	}
}

void FIFO(int vaddr, int &k)	//FIFOҳ���û�����
{
	int b;					// �ڴ���
	int pn;					// ��ǰҪ���ʵ�ҳ��
	int pp;					// ������̭��ҳ��
	int offset;				// ҳ��ƫ��
	unsigned int paddr;		// �����ַ
	int mf;					// �޸��־

	mf = vaddr % 2;				// ����vaddr�����λ�����޸ı�־
	pn = vaddr / psize;
	offset = vaddr % psize;

	pp = ps[k];				// ȡ����Ҫ����̭��ҳ��
	b = ptab[pp].framenum;// ȡ������̭ҳ���ڵ��ڴ���
	if (ptab[pp].mflag == 1)
		cout << "���û���" << pp << "��ҳ���̺���̭,";
	else
		cout << "���û���" << pp << "��ҳֱ�ӱ���̭,";
	// �޸�ҳ��
	ptab[pp].sflag = 0;		// ��ppҳ�Ѳ����ڴ�ı�־
	ptab[pp].framenum = 0;	// ����ϵͳʵ���ϲ�������0����
	ptab[pp].aflag = 0;		// �˴���0ֻ��Ϊ����ʾҳ�����
	ptab[pp].mflag = 0;		// �˴���0ֻ��Ϊ����ʾҳ�����
	ptab[pn].sflag = 1;		// pnҳ�����ڴ�
	ptab[pn].framenum = b;
	ptab[pn].aflag = 1;
	ptab[pn].mflag = mf;

	ps[k] = pn;				// ҳ�����
	k = (k + 1) % BN;			// ����ѭ������ps��ָ��

	paddr = b * psize + offset;	/*�γ������ַ*/
	cout << "���ַ" << vaddr << "���ڵ�" << pn << "ҳ����" << b
		<< "����,��Ӧʵ��ַ��" << paddr << endl;		//������Ե�ַ
}

bool response(int vaddr, int &n)
{
	static int k = 0;			// FIFOҳ��ѭ�������У�k��ָ��ҳ�ǽ�����̭��ҳ
	static int bn = 0;		// �ѷ�����ý��̵��ڴ����
	int b, bb;				// b������õ����ڴ���
	int pn;					// ��ǰҪ���ʵ�ҳ��
	int offset;				// ҳ��ƫ��
	unsigned int paddr;		// �����ַ
	int mf;					// �޸ı�־

	mf = vaddr % 2;				// ����vaddr�����λ�����޸ı�־
	pn = vaddr / psize;
	offset = vaddr % psize;

	if (pn >= PN)				// ��ַԽ��
	{
		cout << "���ַ" << vaddr << "���ڵ�ҳ��Ϊ" << pn << "������ַԽ�����!" << endl;
		return false;
	}

	if (ptab[pn].sflag == 1)	// �����ʵ�ҳ�����ڴ�
	{
		cout << "���ַ" << vaddr << "���ڵ�" << pn << "ҳ�Ѿ����ڴ��"
			<< ptab[pn].framenum << "���У����Ӧ�������ַΪ ";
		paddr = ptab[pn].framenum*psize + offset;
		cout << paddr << endl;
		if (ptab[pn].mflag == 0 && mf == 1)
			ptab[pn].mflag = mf;	// �޸�ҳ�����޸ı�־λ
	}
	else		// ����ȱҳ�ж�
	{
		if (bn < BN)			// �����ڴ��ɷ���
		{
			bb = rand();
			b = bb * 2 + bb % 2;	// �����ڴ��Ų�����0x7fff * 2����65535��
			ps[bn] = pn;		// ҳ�����
			bn++;			// �ѷ�����ý��̵��ڴ������1

			// �޸�ҳ��
			ptab[pn].sflag = 1;
			ptab[pn].framenum = b;
			ptab[pn].aflag = 1;
			ptab[pn].mflag = mf;

			paddr = b * psize + offset;	// �����Ӧ�������ַ(�ض�λ)

			cout << "���ַ" << vaddr << "���ڵ�" << pn << "ҳ�����ڴ��" << b << "���У�";
			cout << "���Ӧ�������ַΪ " << paddr << endl;
		}
		else		// ȱҳ�ж��з���ҳ���û�
		{
			n++;	// ҳ���û�������1
			FIFO(vaddr, k);	// ����FIFOҳ���û��㷨
		}
	}	// ȱҳ�ж����
	cout << "ҳ�Ŷ��У�";
	for (int i = 0; i < BN; i++)
		cout << ps[i] << ' ';
	cout << endl;
	return true;
}

void init()	// ��ʼ��
{
	int i;
	ps = new int[BN];			// ����FIFOҳ�Ŷ��пռ�
	for (i = 0; i < BN; i++)
		ps[i] = -1;			// ��ʼ��ҳ�Ŷ���Ϊ��
	ptab = new pagetable[PN];	// ����ҳ��ռ�
	for (i = 0; i < PN; i++)		// ��ʼ��ҳ��
	{
		ptab[i].sflag = 0;
		ptab[i].mflag = 0;
		ptab[i].aflag = 0;
		ptab[i].framenum = 0;
	}
}

int main()
{
	int *pqueue;		// ָ��ҳ�����ô���ָ��	
	int L;				// �ý��̵�ҳ�����ô��ĳ���
	int nn = 0;			// ����ͳ��ҳ���û�����
	int i, vaddr, vd, pn;
	bool flag;

	srand((unsigned int)time(NULL));	// ��������еġ����ӡ�(ʹ�õ�ǰʱ��Ϊ����)

	cout << "��������̵�ҳ����";
	cin >> PN;
	cout << "�����������ý��̵��ڴ������";
	cin >> BN;
	cout << "������ý��̵�ҳ�����ô��ĳ��ȣ�";
	cin >> L;
	cout << endl;

	init();	// ��ʼ��

	pqueue = new int[L];		// ����ҳ�����ô��ռ�
	for (i = 0; i < L; i++)
		pqueue[i] = -1;		// ��ʼ��ҳ�����ô�

	for (i = 0; i < L; i++)
	{
		vd = rand();			//���ʴ���ҳ���������ģ��
		vaddr = vd * PN / 8;		//rand()���ɵ������������0x7fff���൱��8ҳ�����ۺϳ�PNҳ��
//		vaddr=vd*(PN+1)/8;	//rand()���ɵ������������0x7fff���൱��8ҳ�����ۺϳ�PNҳ��
							//PN+1��Ϊ��ʹ֮���ܲ�������ַԽ�硰��
		pn = vaddr / psize;		// �����ҳ��
		pqueue[i] = pn;		// ��ҳ�Ŵ���ҳ�����ô���
		flag = response(vaddr, nn);
		if (!flag)			//��������ַԽ�磬���������
		{
			L = i + 1;			//�����ѷ��ʵ�ҳ��
			break;
		}
		Sleep(3000 + (rand() % 5) * 2000);
	}

	cout << "\nҳ�����ô�Ϊ��";
	for (i = 0; i < L - 1; i++)
		cout << pqueue[i] << ',';
	cout << pqueue[i] << endl;
	cout << "ҳ���û�����Ϊ " << nn << endl;

	cout << "\n����ҳ���Ϊ(�����ڴ��ҳ��Ӧ���ڴ��ź��޸ı�־��Ч)��" << endl;
	Printptab();	//���ҳ��

	delete[]ps;
	delete[]ptab;
	delete[]pqueue;
}