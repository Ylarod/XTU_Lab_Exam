// Problem: 1255
// Solution: 1871149
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1168KB





						
#include <stdio.h>
#include <math.h>
int main()
{
    int n,a,b,c,d,e,f,g;
    double z;
    scanf("%d",&n);//n����������
    for(z=1; n>0; n--)
    {
        scanf("%d %d",&a,&b);//ab������������߳�
        if (a<b)
        {
            a=a+b;
            b=a-b;
            a=a-b;
        }//��ifȷ��aΪ�ϴ����
/*��������Ϊб��*/        c=a*a+b*b;
        z=sqrt(c);
        d=z;
        e=c-d*d;//e=0ʱ������Ϊ����
 /*��������Ϊֱ�Ǳ�*/       c=a*a-b*b;
        z=sqrt(c);
        g=z;
        f=c-g*g;//f=0ʱ������Ϊ����
        if (f==0&&a!=b)
        {
            printf("%d\n",g);
        }
        else
        {
            if (e==0&&a!=b)
            {
                printf("%d\n",d);
            }
            else
                printf("None\n");
        }
    }
    return 0;
}

				

