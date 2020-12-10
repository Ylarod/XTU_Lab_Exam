// Problem: 1120
// Solution: 1960198
// Language: G++
// Result: Accepted
// Time: 187MS
// Memory: 1248KB





						
#include <stdio.h>
int i;
int judge(int x)
{
    if(x==1) return 0;
    
    for(i=2; i*i<=x; i++)
    {
        if(x%i==0) return 0;
    }
    return 1;
}
int main()
{
    int k;
    scanf("%d",&k);
    while(k!=0)
    {
        int i,n;
        for(i=2; i<=k/2; i++)
        {
            if(judge(i))
            {
                n = k-i;
                if(judge(n))
                {
                    printf("%d %d\n",i,n);
                    break;
                }
            }
        }
        scanf("%d",&k);
    }
    return 0;
}

				

