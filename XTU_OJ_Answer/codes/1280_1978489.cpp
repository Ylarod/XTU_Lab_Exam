// Problem: 1280
// Solution: 1978489
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1256KB





						
#include <stdio.h>
#include <string.h>
int main()
{
    char a[1002];
    int quan[1002]={1,1,26},i,j,p=1000000007;
    __int64 t=1;
        for(i=2;i<1002;i++)
        {
            t = t*26%p;
            quan[i] = t;
        }
    while(scanf("%s",a)!=EOF)
    {
        int lena,sum = 0;
        lena = strlen(a);
        for(i=-1,t=1;i<lena;i++)
        {
            t = t*quan[lena-i]%p;
            sum += t;
            sum = sum%p;
            t = a[i+1]-97;
        }
        printf("%d\n",sum);
    }
    return 0;
}

				

