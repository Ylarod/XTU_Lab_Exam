// ************* Disk.cpp ****************
#include "Disk.h"
// 驱动器类型
char DriveType[][30]={"DRIVE_UNKNOWN","NO_THIS_DRIVE","DRIVE_REMOVABLE",
		"DRIVE_FIXED","DRIVE_REMOTE","DRIVE_CDROM","DRIVE_RAMDISK"};

int main()
{
	disk objdisk;
	Disk theDisk=&objdisk;
	objdisk.hDisk=NULL;		//句柄初始为空
	char choice;
	bool runFlag=true;
	int openFlag;
	//扫描驱动器，寻找可移动磁盘作为初始磁盘
	scandrivetype(theDisk);

	while (runFlag)
	{
		if (theDisk->hDisk==NULL)	//打开磁盘
			openFlag=opendisk(theDisk);
		if (openFlag==NULL)		//若打开失败，显示出错信息
		{
			printf("\n\topen disk failed\n");
			printf("\tdisk %c: may be not existence\n\n",theDisk->driveletter);
			break;
		}
		if (openFlag==-1)
		{
			printf("\n\tdisk %c: can't be read\n",theDisk->driveletter);
			if (theDisk->driveType==5)	//若是光驱
				printf("\tthere is no CD-ROM in drive %c:",theDisk->driveletter);
		}
		choice=interwindow(theDisk);
		if (choice=='6')
		{
			printf("\n\n");
			runFlag=false;			//退出循环
			continue;
		}
		switch(choice)
		{
		case '1' : if (phyysicalDisk(theDisk) == false)
					   printf("\n\tcan't read disk information\n");
					break;
		case '2' : if (partitionInfo(theDisk)==false)
					   printf("\n\tGet the information of partition Error.\n");
				   break;
		case '3' : if (!theDisk->writeFlag)
					   printf("\n\tDrive %c can't be written\n",theDisk->driveletter);
					else if (sectorWrite(theDisk) == false)
					   printf("\n\tWrite sector failed\n");
					break;
		case '4' : sectorDump(theDisk);
				   break;
		case '5' : changeDrive(theDisk); break;
		default  : printf("\n\tWrong choice\n");
		}
		printf("\n\n\tPress \"Enter\" key to continue ");
		_flushall();		//清除缓冲区
		getchar();		//等待按键
	}
	if (theDisk!=NULL)	//关闭磁盘句柄
		CloseHandle(theDisk->hDisk);
}

// 功能选择窗口
char interwindow(Disk theDisk)
{
	system("cls");		//清屏
	char choice;
	char chyn[][6]={" not "," "};
	printf("\n\n\t*************** disk I/O test ***************\n");
	printf("\n\t  Current disk is %c:, ",theDisk->driveletter);
	printf("It can%sbe written\n\n",chyn[theDisk->writeFlag]);
	printf("\n\t Push  1  to get the information of disk\n");
	printf("\t Push  2  to get the information of partition\n");
	printf("\t Push  3  to write information to a sector\n");
	printf("\t Push  4  to read a sector from disk\n");
	printf("\t Push  5  to change the drive for I/O\n");
	printf("\t Push  6  to exit from the test\n\n");
	printf("\t you choice is : ");
	scanf("%c",&choice);
	_flushall();		//清除键盘输入缓冲区
	return choice;
}

UINT getdrivetype(char drivel)
{
	char rootdir[]=" :\\";
	UINT type;
	rootdir[0]=drivel;		//构成跟目录字符串"x:\"
	type=GetDriveType(rootdir);
	return type;
}

void scandrivetype(Disk theDisk)
{
	char drivel='C';
	UINT type;
	while ((type=getdrivetype(drivel))!=1)
	{
		if (type==2) {	//找到可移动磁盘
			theDisk->driveletter=drivel;	//初始盘符是U盘盘符
			theDisk->driveType=type;
			theDisk->writeFlag=true;		//设定对U盘可写
			break;
		}
		drivel++;
	}
	if (type==1) {	//未找到可移动磁盘
		theDisk->driveletter='C';	//初始盘符设为'C'
		theDisk->driveType=3;		//初始值为硬盘
		theDisk->writeFlag=false;	//不可写
	}
}

bool partitionInfo(Disk theDisk)	// 获取磁盘分区信息并显示
{	// 光驱中无光盘时能获取部分分区信息
	char yesno[][6]={"No","Yes"};
	char PartitionType[][30]={"PARTITION_ENTRY_UNUSED","PARTITION_FAT_12",
		"PARTITION_XENIX_1","PARTITION_XENIX_2","PARTITION_FAT_16",
		"PARTITION_EXTENDED","PARTITION_HUGE","PARTITION_IFS"};
	int v[]={14,15,65,99,192};
	char type[][30]={"PARTITION_XINT13","PARTITION_XINT13_EXTENDED",
		"PARTITION_PREP","PARTITION_UNIX","VALID_NTFT"};
	DWORD ReturnSize;
	HANDLE hDisk=theDisk->hDisk;
	PARTITION_INFORMATION partitionInfo;
	PARTITION_INFORMATION *pp=&partitionInfo;
	int flag=DeviceIoControl(hDisk,IOCTL_DISK_GET_PARTITION_INFO,NULL,0,
		pp,50,&ReturnSize,NULL);
	if (!flag)	//若调用DeviceIoControl函数失败则返回0
		return false;
	printf("\n\n\tPARTITION INFORMATION  (Drive %c:)\n\n",theDisk->driveletter);
	printf("\tStartingOffset : %I64d\n",pp->StartingOffset);
	printf("\tPartitionLength : %I64d\n",pp->PartitionLength);
	printf("\tHiddenSectors : %d\n",pp->HiddenSectors);
	printf("\tPartitionNumber : %d ( %c: )\n",pp->PartitionNumber,theDisk->driveletter);
	int n=pp->PartitionType;
	if (n<8)
		printf("\tPartitionType : %s\n",PartitionType[n]);
	else
	{
		for (int i=0,flag=0;i<5;i++)
		{
			if (n==v[i])
			{
				flag=1;
				printf("\tPartitionType : %s\n",type[i]);
				break;
			}
		}
		if (!flag)
			printf("\tPartitionType : %d\n",n);
	}
	printf("\tBootIndicator : %s\n",yesno[pp->BootIndicator]);
	printf("\tRecognizedPartition : %s\n",yesno[pp->RecognizedPartition]);
	printf("\tRewritePartition : %s\n",yesno[pp->RewritePartition]);
	return true;
}

void changeDrive(Disk &theDisk)
{
	char drivel;
	char yesno[][6]={"false","true"};
	UINT type;
	printf("\n\tcurrent driveletter is %c\n",theDisk->driveletter);
	printf("\tinput new driveletter : ");
	scanf("%c",&drivel);
	_flushall();		//清除键盘输入缓冲区
	if (drivel=='\0'||drivel=='\n') //若直接键入回车键
	{
		printf("\n\n\tDrive does not change.\n");
		return;
	}
	drivel=toupper(drivel);	//转换成大写字母
	if (theDisk->driveletter!=drivel)//若输入的驱动器符与当前驱动器符不同
	{
		type=getdrivetype(drivel);//获取新指定驱动器的类型
		if (type==1)	//新指定的驱动器不存在
		{
			printf("\n\tdrive %c: may not be existence\n",drivel);
			printf("\tDrive does not change.\n");
			return;
		}
		theDisk->driveType=type;		//保存驱动器类型
		theDisk->driveletter=drivel;	//保存盘符
		printf("\n\t%c: is %s\n",drivel,DriveType[type]);//显示驱动器类型
		if (type==2)	//若新指定的驱动器是U盘
			theDisk->writeFlag=true;	//允许对新指定驱动器执行写操作
		else
			theDisk->writeFlag=false;	//其它类型的驱动器都不允许写盘
		printf("\n\n\tNew drive is : %c\n",drivel);	//显示新驱动器符
		printf("\twriteFlag is : %s\n",yesno[theDisk->writeFlag]);//显示新驱动器能否“写”
		theDisk->driveletter=drivel;	//新指定驱动器作为当前驱动器
		if (theDisk)	//关闭原来的磁盘句柄
		{
			CloseHandle(theDisk->hDisk);
			theDisk->hDisk=NULL;	//新驱动器尚未打开，其句柄为0
		}
	}
	else	//新指定驱动器与当前驱动器向相同
		printf("\n\n\tDrive does not change.\n");
}

// 将获得磁盘的物理参数显示出来
bool phyysicalDisk(Disk theDisk)
{
	char mediatype[][40]={"Format is unknown","5.25\", 1.2MB, 512 bytes/sector",
		"3.5\", 1.44MB, 512 bytes/sector","3.5\", 2.88MB, 512 bytes/sector",
		"3.5\", 20.8MB, 512 bytes/sector"," "," "," "," "," "," ",
		"RemovableMedia","FixedMedia"};
	if (theDisk->hDisk==NULL)
	{
		printf("there is no disk available!\n");
		return false;
	}
	DWORD ReturnSize;
	int flag=DeviceIoControl(theDisk->hDisk,IOCTL_DISK_GET_DRIVE_GEOMETRY,
		NULL,0,&(theDisk->theSupportedGeometry),50,&ReturnSize,NULL);
	if (!flag)
		return false;
	printf("\n\n\tDISK INFORMATION  (Drive %c:)\n\n",theDisk->driveletter);
	DWORD sectorsize=theDisk->theSupportedGeometry.BytesPerSector;
	printf("\tBytesPerSector : %d\n",sectorsize);
	printf("\tSectorPerTrack : ");
	printf("%d\n",theDisk->theSupportedGeometry.SectorsPerTrack);
	printf("\tTrackPerCylinder : ");
	printf("%d\n",theDisk->theSupportedGeometry.TracksPerCylinder);
	printf("\tCylinders : %d\n",theDisk->theSupportedGeometry.Cylinders);
	int mtype=theDisk->theSupportedGeometry.MediaType;
	printf("\tMediaType : %s\n\n",mediatype[mtype]);
	return true;
}

//打开磁盘，获得句柄存入返回的一个disk结构
int opendisk(Disk &theDisk)
{
	char buffer[]="\\\\.\\ :";
	buffer[4]=theDisk->driveletter;
	DWORD ReturnSize;
	// 调用API函数CreateFile( )打开磁盘，返回的磁盘句柄存于hDisk
	theDisk->hDisk=CreateFile(
		buffer,	//根目录路径名，例如 \\.\C
		GENERIC_READ|GENERIC_WRITE, 	//可读、可写。此处可用0xc0000000
FILE_SHARE_READ|FILE_SHARE_WRITE, //读写共享模式。此处可用3
		NULL,
		OPEN_EXISTING,		//若对象存在，则打开它；否则，本操作失败
		FILE_FLAG_RANDOM_ACCESS|FILE_FLAG_NO_BUFFERING,
NULL
		); 	//失败时返回INVALID_HANDLE_VALUE(即-1)
	if (theDisk->hDisk==INVALID_HANDLE_VALUE)//若驱动器不存在
	{
		theDisk->hDisk=NULL;
		return 0;
	}
	//获取它的物理参数(磁盘打开后一般需执行此操作后才能正确对磁盘读/写)
	int flag=DeviceIoControl(theDisk->hDisk,IOCTL_DISK_GET_DRIVE_GEOMETRY,
		NULL,0,&(theDisk->theSupportedGeometry),50,&ReturnSize,NULL);
	if (!flag)
		return -1;
	return 1;
}

// 读取指定的磁盘区域的内容并将它们显示出来(文件和十六进制两种方式)
bool sectorDump(Disk theDisk)
{
	if (theDisk->hDisk==NULL)
	{
		printf("\n\tthere is no disk available!\n");
		return false;
	}
	DWORD sectorsize=theDisk->theSupportedGeometry.BytesPerSector;
	char *RdBuf=new char[sectorsize];	//动态分配输入缓冲区
	int j,logSectorNumber;

	//从磁盘某扇区中读出内容并显示(文件和十六进制两种方式)
	printf("\n\n\tPlease Input the Sector NO to read from : ");
	scanf("%d",&logSectorNumber);getchar();
	if (!sectorRead(theDisk,logSectorNumber,RdBuf))
	{
		printf("\n\tError occurred while reading the sector!\n");
		delete []RdBuf;		//释放输入缓冲区
		return false;
	}
	printf("\nText Content : \n");
	for (DWORD i=0;i<sectorsize;i++)
		printf("%c",RdBuf[i]);
	printf("\n\n Hex Content :\n");
	for (int i=0,j=0;i<sectorsize;i++)
	{
		if (j%16==0)
			printf("\n %03x : ",j);
		printf("%02x ",(BYTE)RdBuf[i]);	//BYTE是单字节整数
		j++;
	}
	printf("\n");
	delete []RdBuf;		//释放输入缓冲区
	return true;
}

// 从某磁盘扇区中读出指定字节数的数据到指定缓冲区RdBuf
BOOL sectorRead(Disk theDisk,unsigned logSectorNumber,char *RdBuf)
{
	DWORD BytesRead;
	DWORD sectorsize=theDisk->theSupportedGeometry.BytesPerSector;
	long sectortomove=logSectorNumber*(theDisk->theSupportedGeometry.BytesPerSector);
	SetFilePointer(theDisk->hDisk,sectortomove,NULL,FILE_BEGIN);
	if (!ReadFile(theDisk->hDisk,RdBuf,sectorsize,&BytesRead,NULL))
		return false;
	return true;
}
// 将用户输入的数据写到指定的磁盘扇区中
BOOL sectorWrite(Disk theDisk)
{
	DWORD BytesWrite;
	DWORD sectorsize=theDisk->theSupportedGeometry.BytesPerSector;
	int logSectorNumber;
	if (theDisk->hDisk==NULL)
	{
		printf("\n\nthere is no disk available!\n");
		return false;
	}
	char *WrBuf=new char[sectorsize];	//动态分配输出缓冲区
	ZeroMemory(WrBuf,sectorsize);	// 输出缓冲区内存空间清零
	// 从指定缓冲区WrBuf写指定字节数的数据到某磁盘扇区中
	printf("\n\n\tPlease Input the sector NO to Write to : ");
	scanf("%d",&logSectorNumber);
	getchar();
	printf("\n\tPlease input the content to write to disk\n\t");
	gets(WrBuf);
	long sectortomove=logSectorNumber*(theDisk->theSupportedGeometry.BytesPerSector);
	SetFilePointer(theDisk->hDisk,sectortomove,NULL,FILE_BEGIN);//读写指针移到指定位置
		if (!WriteFile(theDisk->hDisk,WrBuf,sectorsize,&BytesWrite,NULL))
	{
		delete []WrBuf;		//释放输出缓冲区
		return false;
	}
	printf("\n\twrite complete successfully\n");
	delete []WrBuf;		//释放输出缓冲区
	return true;
}