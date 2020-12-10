// Problem: 1098
// Solution: 1927267
// Language: G++
// Result: Accepted
// Time: 125MS
// Memory: 6992KB





						
#include <stdio.h>
int b[1000001]= {0};
int main()
{
    int i,j,x,y=5,judge=1,a[500000]= {2,3},ab,bb,k;
    for(i = 2; a[i-1]<1000000; y++)
    {
        judge = 1;
        for(x=0; a[x]*a[x]<=y; x++)
        {
            if(y%a[x]==0)
            {
                judge = 0;
                break;
            }
        }
        if(judge==1)
        {
            a[i] = y;
            i++;
        }
    }
    for(i=0; a[i]<=1000000; i++)
    {
       b[a[i]] = 1;
    }
    for(i=3; i<1000001; i++)
    {
        b[i] += b[i-1];
    }
    scanf("%d",&k);
    while(k--)
    {
        scanf("%d %d",&ab,&bb);
        if(ab>bb){
            ab = ab+bb;
            bb = ab-bb;
            ab = ab-bb;
        }
        printf("%d\n",b[bb]-b[ab-1]);
    }
    return 0;
}

				

