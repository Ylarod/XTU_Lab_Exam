// Problem: 1177
// Solution: 1963141
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1280KB





						
#include <stdio.h>
int main()
{
    unsigned __int64 f[67][67];
    int i,j,k,sum,judge;
    f[0][0] = 1;
    f[1][0] = 1;
    f[1][1] = 1;
    for(i=2; i<=66; i++)
    {
        f[i][0] = 1;
        for(j=1; j<i; j++)
        {
            f[i][j] = f[i-1][j]+f[i-1][j-1];
        }
        f[i][j] = 1;
    }
    while(scanf("%d %d",&i,&j)&&i+j!=0)
    {
        printf("%I64u\n",f[i+j][i]);
    }
    return 0;
}

				

