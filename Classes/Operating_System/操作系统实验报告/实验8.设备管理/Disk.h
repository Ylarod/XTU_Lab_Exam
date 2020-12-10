// *********** Disk.h ***********
#include <windows.h>
#include <winioctl.h>	// 包含了DISK_GEOMETRY等定义
#include <stdio.h>
#include <iostream>

using namespace std;
//Disk是结构指针
typedef struct disk {
	HANDLE hDisk;		//磁盘句柄
	CHAR driveletter;	//驱动器名(盘符)
	UINT driveType;		//驱动器类型
	BOOL writeFlag;		//可写标志
	DISK_GEOMETRY theSupportedGeometry;
} *Disk;		//Disk是指向disk结构的指针

// 以下程序中用到的几个函数
// 打开磁盘，并获得相关物理信息，存入返回的disk结构的theSupportedGeometry项中
int opendisk(Disk &theDisk);
char interwindow(Disk theDisk);		// 功能选择接口
bool phyysicalDisk(Disk theDisk);	// 获得磁盘的物理参数显示出来
// 读取特定的磁盘区域的内容并将它们显示出来(文件和十六进制两种方式)
bool sectorDump(Disk theDisk);
// 从某磁盘扇区中读出指定字节数的数据到指定缓冲区RdBuf
BOOL sectorRead(Disk theDisk,unsigned logSectorNumber,char *RdBuf);
// 从指定缓冲区WrBuf写指定字节数的数据到某磁盘扇区中
BOOL sectorWrite(Disk theDisk);
bool partitionInfo(Disk theDisk);	//显示分区信息
void changeDrive(Disk &theDisk);	//改变驱动器
UINT getdrivetype(char drivel);		//获取驱动器类型
void scandrivetype(Disk theDisk);	//扫描驱动器，寻找可移动磁盘