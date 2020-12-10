// Problem: 1258
// Solution: 1961813
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
    while(k--){
        char order;
        char b[12],a[102];
        int i,j,m,n,x,y,ls;
        scanf("%d %d",&n,&m);
        getchar();
        for(j=0;j<=100;j++)
            {
                a[j] = j;
            }
        while(m)
        {
            scanf("%c %d %d",&order,&x,&y);
            getchar();
            x--;
            if(order=='L')
            {
                for(j=1;j<=n;j++)
                {ls = j+y;
                    if(j+y>n) ls -= n;
                    b[j] = a[x*n+ls];
                }
                for(j=1;j<=n;j++)
                {
                    a[x*n+j] = b[j];
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
            m--;

        }
                for(j=1;j<=n*n;j++)
                {if(j!=1) printf(" ");
                    printf("%d",a[j]);
                }
            printf("\n");
    }
    return 0;
}

				

