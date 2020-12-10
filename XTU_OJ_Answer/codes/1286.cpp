// Problem: 1286
// Solution: 1965796
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1252KB





						
#include <stdio.h>
long long a[1002]={1,2};
int main()
{
    int m,i;
    for(i=2;i<1000;i++) a[i] = a[i-1]+a[i-2];
    // printf("%lld\n",a[i]);
    long long n;
    while(scanf("%I64dd",&n)!=EOF)
    {
        int sum=0;
        m = n-1;
        if(n<4) printf("%d\n",m);
        else
        {
            n -= 3;
            sum += 2;
            for(i=2;n>=0;i++)
            {
                if(a[i-1]<=n)
                    sum++;
                n -= a[i-1];
            }
            printf("%d\n",sum);
        }
    }
    return 0;
}

				

