#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>	//Sleep()
int main(int argc,char **argv) 	//ִ��ʱ�ɴ������ĳ���
{
	unsigned int wt,x=1;
	if (argc>=2)
		x=1+atoi(argv[1]);
	x=x*(unsigned int)time(NULL);
	srand(x);	// ʹ�õ�ǰʱ��Ϊ������е�"����"
	char Title[30]="Process ";
	if (argc>=2)
	{
		strcat(Title,argv[1]);
		SetConsoleTitle(Title);	//���ñ�����
	}
	for (int i=1;i<=30;i++)
	{
		//��ʾ�����������е���Ϣ�������������argv[1]��Ϊ���̵ı��
		printf(" %2d : Process ",i);
		if (argc>=2)
			printf("%s ",argv[1]);
		printf("��������!\n");
		wt = 200 + rand() % 500 + rand() % 1000;
		wt= rand() % wt + 300;
		Sleep(wt);	//˯�ߵȴ�200~2000ms
	}
	return 0;
}
