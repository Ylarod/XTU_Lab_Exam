// Problem: 1123
// Solution: 1965160
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1252KB





						
#include <stdio.h>
int a[1001];
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,k,n0;
        scanf("%d %d",&n,&k);
        n0 = n;
        while(n--)
        {
            //
            scanf("%d",&a[n0-n-1]);
        }
      //  printf("≤‚ ‘1\n");
        int judge=1,i,j;
        for(i=k;i<n0;i++)
        {
           // printf("a[%d]:%d,a[%d]:%d\n",k-1,a[k-1],i,a[i]);
            if(a[k-1]!=a[i])
            {
                judge = 0;
                break;
            }
        }
       // printf("juge:%d",judge);
        if(judge)
        {
            for(i=k-2;i>=0;i--)
            {
                if(a[k-1]==a[i])
                    k--;
                else
                    break;
            }
            k--;
            printf("%d\n",k);
        }else
        {
            printf("-1\n");
        }
    }
    return 0;
}

				

