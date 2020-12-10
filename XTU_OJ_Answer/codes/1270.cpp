// Problem: 1270
// Solution: 1966581
// Language: G++
// Result: Accepted
// Time: 671MS
// Memory: 70812KB





						
#include <stdio.h>
long long a[8877693];
int b[12]={0};
int main()
{
    int i,j,k,x,y,z,m,sl=10,n;
    for(i=0;i<10;i++) a[i] = i;
    for(i=1;sl<8877691;i++)
    {
        for(j=0;j<11;j++) b[j] = 0;
        j = a[i];
        while(j)
        {
            x = j%10;
            j /= 10;
            b[x] = 1;
        }
        for(k=0;k<10;k++)
        {
            if(b[k]!=1)
            {
                a[sl] = a[i]*10+k;
                sl++;
            }
        }
    }
    while(scanf("%d",&m)!=EOF)
    {
        printf("%I64d\n",a[m-1]);
    }
    return 0;
}

				

