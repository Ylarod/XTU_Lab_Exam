// Problem: 1121
// Solution: 1960535
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1252KB





						
#include <stdio.h>
int main()
{
    int n;
    while(scanf("%d",&n)&&n!=0)
    {
        int sum=1,judge,i,j;
        sum = n;
        if(n==1){
            printf("0\n");
            continue;
        }
        for(i=2; i*i<=n; i++)
        {
            judge = 0;
            while(n%i==0)
            {
                n /= i;
                judge = 1;
            }
            if(judge) sum = sum/i*(i-1);
        }
        if(n!=1) sum = sum/n*(n-1);
        printf("%d\n",sum);
    }
    return 0;
}

				

