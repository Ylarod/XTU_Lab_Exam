// Problem: 1194
// Solution: 1963251
// Language: G++
// Result: Accepted
// Time: 31MS
// Memory: 8180KB





						
#include <stdio.h>
long long a[1002][1002],f[1002];
int main()
{
    int i,j,k,n,m,sum,judge,mo=1000000007;
    a[0][0] = 1;
    a[1][0] = 1;
    a[1][1] = 1;
    for(i=2;i<=1000;i++)
    {
        a[i][0] = 1;
        for(j=1;j<i;j++)
        {
            a[i][j] = (a[i-1][j]+a[i-1][j-1])%mo;
        }
        a[i][j] = 1;
    }
    f[0] = 1;
    f[1] = 0;
    f[2] = 1;
    for(i=3;i<=1000;i++)
    {
        f[i] = (i-1)*(f[i-1]+f[i-2])%mo;
    }
    while(scanf("%d %d",&i,&j)&&i+j!=0)
    {
        printf("%I64d\n",a[i][j]*f[j]%mo);
    }
    return 0;
}

				

