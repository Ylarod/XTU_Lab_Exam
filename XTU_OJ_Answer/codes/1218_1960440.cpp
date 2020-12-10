// Problem: 1218
// Solution: 1960440
// Language: G++
// Result: Accepted
// Time: 265MS
// Memory: 1252KB





						
#include <stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    while(n--)
    {
        int c,d,sum=0,judge,i,j,z;
        scanf("%d %d",&c,&d);
        sum = c+d;
        z = 1;
        if(sum<4)
        {if(sum==1)
            printf("1\n");
            if(sum==2)
            printf("2\n");
            if(sum==3)
            printf("2\n");
            continue;
        }
        for(i=2,j=0; i*i<=sum; i++)
        {
            j = 0;
            while(sum%i==0)
            {
                sum /= i;
                j++;
            }
            z *= (j+1);
        }
        if(sum!=1) z *= 2;
        printf("%d\n",z);
    }
    return 0;
}

				

