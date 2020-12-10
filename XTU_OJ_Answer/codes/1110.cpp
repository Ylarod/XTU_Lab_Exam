// Problem: 1110
// Solution: 1850766
// Language: G++
// Result: Accepted
// Time: 0MS
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
        if(a[i]%2==1)
        s++;
        }
        printf("%d\n",s);
    }
}
				

