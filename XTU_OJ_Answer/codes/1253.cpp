// Problem: 1253
// Solution: 1965381
// Language: G++
// Result: Accepted
// Time: 796MS
// Memory: 1252KB





						
#include <stdio.h>
int main()
{
    int n,n0,a[1002];
    while(scanf("%d",&n)!=EOF)
    {
        n0 = n;
        while(n--)
        {
       //    printf("n:%d",n);
            scanf("%d",&a[n0-n-1]);
        }
      //  printf("≤‚ ‘0\n");
        int i,j,sum=0,b[1002];
       // printf("≤‚ ‘11\n");
        for(i=0;i<n0;i++)
        {
            b[i] = 1;
        }
        int judge=1,cishu=0;
       // printf("≤‚ ‘1\n");
        while(judge)
        {
           // printf("≤‚ ‘2\n");
            judge = 0;
            cishu++;
            for(i=0;i<n0;i++)
            {
                if(b[i])
                {
                    if(sum>=a[i])
                    {
                        sum++;
                        b[i] = 0;
                        judge = 1;
                    }
                }
            }
            if(judge)
            {
                cishu++;
                judge = 0;
                for(i=n0-1;i>=0;i--)
                {
                    if(b[i])
                    {
                        if(sum>=a[i])
                        {
                            sum++;
                            b[i] = 0;
                            judge = 1;
                        }
                    }
                }
            }
           // printf("≤‚ ‘3\n");
        }
        cishu -= 2;
        printf("%d\n",cishu);
    }
    return 0;
}
				

