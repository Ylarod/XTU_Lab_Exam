#define BUFSIZE MAX_PATH
#define HISNUM	20			//�����Ա���20����ʷ����
char buf[BUFSIZE];

//������ʷ����Ľṹ
typedef struct ENV_HISTORY {
	int start;					// ���е�ͷָ��
	int end; 					// ���е�βָ��
	char his_cmd[20][128];		// ��������(˳��ṹ�Ķ���)
} ENV_HISTORY;
ENV_HISTORY envhis;			// ������б���(Ϊ���з����ڴ�ռ�)
//˵������envhis��ȫ�ֱ���(����̬����)�������Աstar,end�г�ֵ0

//�����ļ���Ŀ¼�����Ϣ�Ľṹ
struct files_Content {
	FILETIME time;			// �ļ�����ʱ��
	char name[200];			// �ļ���
	int type;		// type=1��ͨ�ļ�, type=0Ŀ¼
	int size;					// �ļ���С
	files_Content *next;		// �������������ָ��
};