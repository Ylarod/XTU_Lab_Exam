// Problem: 1087
// Solution: 1983832
// Language: G++
// Result: Accepted
// Time: 46MS
// Memory: 1280KB





						
#include <stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    while(n!=-1)
    {
        int i,result=1;
        for(i=1;i<=n;i++)
            result += i;
        printf("%d\n",result);
        scanf("%d",&n);
    }
    return 0;
}
				

