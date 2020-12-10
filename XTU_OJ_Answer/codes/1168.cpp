// Problem: 1168
// Solution: 1959288
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1248KB





						
#include <stdio.h>
int main()
{
    int f[1001],i,m,n,  mo=1000003;;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        f[1]=m;f[2]=m*(m-1)%mo;f[3]=m*(m-1)*(m-2)%mo;
        if(n>3)
        for(i=4;i<=n;i++)
        {
            f[i]=(f[i-1]*(m-2)%mo+f[i-2]*(m-1)%mo)%mo;
        }
        printf("%d\n",f[n]%mo);
    }
    return 0;
}
				

