// Problem: 1054
// Solution: 1888323
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1172KB





						
#include <stdio.h>
int main()
{
    /*蛐蛐大神保平安*/
    int n,i=0,counttwo=0,j;
    long long a[1001],b[1001];
    scanf("%d",&n);
    while(n)
    {
        counttwo=0;
        for(i=0; i<n; i++)
        {
            scanf("%lld",&a[i]);
            b[i]=a[i]*a[i];
      /*      if(b[i]==1)
                counttwo--;
                */
        }
        for(j=0; j<n; j++)
        {
            for(i=0; i<n; i++)
            {
                if(a[j]==b[i])
                    counttwo++;
            }
        }
        printf("%d\n",counttwo);
        scanf("%d",&n);
    }
    return 0;
}

				

