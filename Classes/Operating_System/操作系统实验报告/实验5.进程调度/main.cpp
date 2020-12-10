#include "schedule.h"
ofstream log1;  //保存进程调度信息的文件
volatile bool exiting;	//是否退出程序

void helpInfo()
{
	cout << "************************************************\n";
	cout << "COMMAND LIST:\n";
	cout << "create process_name process_length (create p0 8)\n";
	cout << "\t append a process to the process list\n";
	cout << "remove process_name (remove p0)\n";
	cout << "\t remove a process from the process list\n";
	cout << "current\t show current runprocess readyList\n";
	cout << "exit\t exit this simulation\n";
	cout << "help\t get command imformation\n";
	cout << "************************************************\n\n";
}

int main()
{
	char name[20] = { '\0' };
	HANDLE hSchedule;	//调度线程的句柄
	log1.open("Process_log.txt");
	helpInfo();
	hSchedule = init();	//hSchedule是调度程序的句柄
	if (hSchedule == NULL)
	{
		cout << "\nCreate schedule-process failed. System will abort!" << endl;
		exiting = true;
	}
	char command[30] = { 0 };
	while (!exiting)
	{
		cout << "COMMAND>";
		cin >> command;
		if (strcmp(command, "exit") == 0)
			break;
		else if (strcmp(command, "create") == 0)
		{
			char name[20] = { '\0' };
			int time = 0;
			cin >> name >> time;
			createProcess(name, time);
		}
		else if (strcmp(command, "remove") == 0)
		{
			cin >> name;
			removeProcess(name);
		}
		else if (strcmp(command, "current") == 0)
			printCurrent();
		else if (strcmp(command, "help") == 0)
			helpInfo();
		else
			cout << "Enter help to get command information!\n";
	}
	exiting = true;

	if (hSchedule != NULL)
	{	//无限等待，直到Schedule进程(线程)终止为止
		WaitForSingleObject(hSchedule, INFINITE);
		CloseHandle(hSchedule);
	}
	log1.close();
	cout << "\n******* End *******\n" << endl;
	return 0;
}