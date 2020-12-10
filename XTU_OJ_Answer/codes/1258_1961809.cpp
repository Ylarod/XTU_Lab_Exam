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
    while(k--){//k控制样例个数
        char order;
        char b[12],a[102];
        int i,j,m,n,x,y,ls;//i代表行 j代表列 均从零开始 其余变量命名与题目一致
        scanf("%d %d",&n,&m);
        getchar();
        for(j=0;j<=100;j++)
            {
                a[j] = j;
            }//生成矩阵
       //     printf("测试0");
        while(m)
        {
            scanf("%c %d %d",&order,&x,&y);//读入命令
            getchar();
            x--;
       //     printf("测试1");
            if(order=='L')//以下四个if是执行命令的功能
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
        //    printf("测试2");
            m--;

        }
        //printf("测试3");
                   //执行完命令之后输出矩阵
                for(j=1;j<=n*n;j++)
                {if(j!=1) printf(" ");//第一个数字以外的数字前面都有一个空格
                    printf("%d",a[j]);
                }
            printf("\n");//输出完一个矩阵换行
    }
    return 0;
}

				

