// Problem: 1280
// Solution: 1978464
// Language: G++
// Result: Accepted
// Time: 46MS
// Memory: 1260KB





						
#include <stdio.h>
#include <string.h>
int p = 1000000007;
int main()
{
    char a[1002];
    int quan[1002]={1,1,26};
    int sum = 0,i,j;
    __int64 t=1;
        for(i=2;i<1002;i++)
        {
            t = t*26%p;
            quan[i] = t;
        }
    while(scanf("%s",a)!=EOF)
    {
        getchar();
        int lena;
        sum = 0;
        lena = strlen(a);
        for(i=0;i<lena;i++)
        {
            t = a[i]-97;
                t = t*quan[lena-i]%p;
            sum += t;
            sum = sum%p;
        }
        t = 1;
        for(i=0;i<lena;i++)
        {
            t = t*26%p;
        }
        sum += t;
        sum = sum%p;
        printf("%d\n",sum);
    }
    return 0;
}

/*abc
bc
abcdefghijklmnopqrstuvwxyz*/

				

