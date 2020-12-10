// Problem: 1297
// Solution: 1970339
// Language: G++
// Result: Accepted
// Time: 46MS
// Memory: 1260KB





						
#include <stdio.h>
#include <math.h>
int b[505]={0};
__int64 a[505]={0};
int zhuanhuan(int c)
{
    if(c>=1&&c<=12)
        c = 32;
    else if(c>=13&&c<=24)
        c = 16;
    else if(c>=25&&c<=48)
        c = 8;
    else if(c>=49&&c<=96)
        c = 4;
    else if(c>=97&&c<=192)
        c = 2;
    else if(c>=193)
        c = 1;
    return c;
}
int jiaohuan(int x,int y)
{
    int c;
    c = a[x];
    a[x] = a[y];
    a[y] = c;
    c = b[x];
    b[x] = b[y];
    b[y] = c;
    return 0;
}
int main()/*����a��ѧ������b������ ͨ���±꽫a b����*/
{
    int n,i=1,i1,c;
    while(scanf("%d %I64d %d",&n,&a[i],&c)!=EOF)
    {
        for(i1=0;i1<i;i1++)
        {
            if(a[i1]==a[i])
            {
                break;
            }
        }
            b[i1] += zhuanhuan(c);//������ת���ɻ���
        if(i1==i)
            i++;
    }//��������
    int num,judge=1;
    num = i-1;
    while(judge)
    {
        judge = 0;
        for(i=1;i<num;i++)
        {
            if(b[i]<b[i+1])
            {
                jiaohuan(i,i+1);
                judge = 1;
            }
        }
    }//ð�ݽ���������
     int k;
     double q,w;
    q = b[1];
    for(i=1;i<=num;i++)
    {
        w = log(b[i]/q)*10+100.5;
        b[i] = w;
    }//������תΪ����
    for(i=1;i<num;i++)
    {
        k = i;
        while(b[i]==b[i+1])
        {
            i++;
        }//Ѱ�һ�����ͬ�������
       //if(b[i]==79) printf("k.i:%d %d\n",k,i);
        judge = 1;
        while(judge)
        {
            judge = 0;
            for(i1=k;i1<i;i1++)
            {
                if(a[i1]>a[i1+1])
                {
                    jiaohuan(i1,i1+1);
                    judge = 1;
                }//if(b[i]==79) printf("%I64d %I64d   ",a[i1],a[i1+1]);
            }//if(b[i]==79)   printf("\n");
        }//ð�ݽ�ѧ������
    }
    for(i=1;i<=num;i++)
        printf("%I64d %d\n",a[i],b[i]);//�������
    return 0;
}

				

