// Problem: 1258
// Solution: 1961809
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1256KB





						
#include <stdio.h>
int main()
{
    int k;
    scanf("%d",&k);
    getchar();
    while(k--){//k������������
        char order;
        char b[12],a[102];
        int i,j,m,n,x,y,ls;//i������ j������ �����㿪ʼ ���������������Ŀһ��
        scanf("%d %d",&n,&m);
        getchar();
        for(j=0;j<=100;j++)
            {
                a[j] = j;
            }//���ɾ���
       //     printf("����0");
        while(m)
        {
            scanf("%c %d %d",&order,&x,&y);//��������
            getchar();
            x--;
       //     printf("����1");
            if(order=='L')//�����ĸ�if��ִ������Ĺ���
            {
                for(j=1;j<=n;j++)
                {ls = j+y;
                    if(j+y>n) ls -= n;
                    b[j] = a[x*n+ls];
                }
                for(j=1;j<=n;j++)
                {
                    a[x*n+j] = b[j];
                   // printf("a%d %d:%d",x+1,j,a[x*n+j]);
                }
            }
            if(order=='R')
            {
                for(j=1;j<=n;j++)
                {ls = j+y;
                    if(j+y>n) ls -= n;
                    b[ls] = a[x*n+j];
                }
                for(j=1;j<=n;j++)
                {
                    a[x*n+j] = b[j];
                }
            }
            if(order=='U')
            {
                for(j=1;j<=n;j++)
                {ls = j+y;
                    if(j+y>n) ls -= n;
                    b[j] = a[(ls-1)*n+x+1];
                }
                for(j=1;j<=n;j++)
                {
                    a[(j-1)*n+x+1] = b[j];
                }
            }
            if(order=='D')
            {
                for(j=1;j<=n;j++)
                {ls = j+y;
                    if(j+y>n) ls -= n;
                    b[ls] = a[(j-1)*n+x+1];
                }
                for(j=1;j<=n;j++)
                {
                    a[(j-1)*n+x+1] = b[j];
                }
            }
        //    printf("����2");
            m--;

        }
        //printf("����3");
                   //ִ��������֮���������
                for(j=1;j<=n*n;j++)
                {if(j!=1) printf(" ");//��һ���������������ǰ�涼��һ���ո�
                    printf("%d",a[j]);
                }
            printf("\n");//�����һ��������
    }
    return 0;
}

				

