// Problem: 1054
// Solution: 1906652
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1164KB





						
                        
#include<stdio.h>
int main()
{
    long long a[1001],m;
    int n,i,j,s,k;
    scanf("%d",&n);
while(n){
    for(i=0;i<n;i++)
    {
        scanf("%lld",&a[i]);
    }
    s=0;
    for(k=0;k<n;k++)
        {
            for(j=0;j<n;j++)
            {
              if(a[k]>=a[j])
               {
                 m=a[j]*a[j];
                 if(a[k]==m) s++;

               }

            }
        }
        printf("%d\n",s);
    scanf("%d",&n);
}
        return 0;
}
				

