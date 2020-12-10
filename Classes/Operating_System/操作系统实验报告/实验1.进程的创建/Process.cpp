#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>	//Sleep()
int main(int argc,char **argv) 	//执行时可带参数的程序
{
	unsigned int wt,x=1;
	if (argc>=2)
		x=1+atoi(argv[1]);
	x=x*(unsigned int)time(NULL);
	srand(x);	// 使用当前时间为随机序列的"种子"
	char Title[30]="Process ";
	if (argc>=2)
	{
		strcat(Title,argv[1]);
		SetConsoleTitle(Title);	//设置标题栏
	}
	for (int i=1;i<=30;i++)
	{
		//显示进程正在运行的信息，其中命令参数argv[1]作为进程的编号
		printf(" %2d : Process ",i);
		if (argc>=2)
			printf("%s ",argv[1]);
		printf("正在运行!\n");
		wt = 200 + rand() % 500 + rand() % 1000;
		wt= rand() % wt + 300;
		Sleep(wt);	//睡眠等待200~2000ms
	}
	return 0;
}
