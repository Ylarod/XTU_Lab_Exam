// Problem: 1307
// Solution: 1964394
// Language: G++
// Result: Accepted
// Time: 46MS
// Memory: 1264KB





						
#include <stdio.h>
int main()
{
    __int64 b[2000],a[66]={1},x,y;
    int i,j,sum,k,unm=1,sumx,sumy;
    for(i=1;i<61;i++)
    {
        a[i] = a[i-1]*2;
     //   printf("a[%d]%llu\n",i,a[i]);
    }
    for(i=2;i<61;i++)
    {
        for(j=i-2;j>=0;j--)
        {
            b[unm] = (a[i]-a[j]-1);
           //  printf("a[%d]:%llu-a[%d]:%llu-1=b[%d]%llu\n",i,a[i],j,a[j],unm,b[unm]);
          // printf("b[%d]%llu\n",unm,b[unm]);
            unm++;
        }
    } //printf("≤‚ ‘");
     scanf("%d",&k);
    while(k--)
    {
        //printf("≤‚ ‘");
        scanf("%I64d %I64d",&x,&y);
        for(i=1,sumx=0;b[i]<x;i++)
        {
            sumx++;
        }
        for(i=1,sumy=0;b[i]<=y;i++)
        {
            sumy++;
        }
        printf("%d\n",sumy-sumx);
   }
    return 0;
}
				

