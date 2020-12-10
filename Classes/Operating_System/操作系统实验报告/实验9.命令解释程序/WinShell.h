#define BUFSIZE MAX_PATH
#define HISNUM	20			//最多可以保存20个历史命令
char buf[BUFSIZE];

//保存历史命令的结构
typedef struct ENV_HISTORY {
	int start;					// 队列的头指针
	int end; 					// 队列的尾指针
	char his_cmd[20][128];		// 队列数组(顺序结构的队列)
} ENV_HISTORY;
ENV_HISTORY envhis;			// 定义队列变量(为队列分配内存空间)
//说明：因envhis是全局变量(属静态变量)，故其成员star,end有初值0

//保存文件或目录相关信息的结构
struct files_Content {
	FILETIME time;			// 文件创建时间
	char name[200];			// 文件名
	int type;		// type=1普通文件, type=0目录
	int size;					// 文件大小
	files_Content *next;		// 构成链表的链接指针
};