// Problem: 1111
// Solution: 1850375
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1160KB





						
#include<stdio.h>
int main()
{
    int i,n;
    int a[101];
    while(scanf("%d",&n))
    {
        if(n==0)
        return 0;
        int s=0;
        for(i=0;i<n;i++)
        {
        scanf("%d",&a[i]);
        if(a[i]%2==0)
        s=s+a[i];
        }
        printf("%d\n",s);
    }
}
				

