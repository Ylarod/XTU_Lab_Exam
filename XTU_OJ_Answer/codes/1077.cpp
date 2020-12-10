// Problem: 1077
// Solution: 1853351
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1164KB





						
#include <stdio.h>
int main()
{
    int a=1,n,count=0,counttwo=0,b=1,c=1;
    scanf("%d",&n);
    while (n!=0)
    {
        printf("case %d:\n",c);
        while (n>0)
        {
            for (count=1; count<n; count++)
            {
                printf(" ");
            }
            for (counttwo=0; counttwo<b; counttwo++)
           {
                printf("%d",a);
            }
            printf("\n");
            n--;
            b++;
            b++;
            a++;
        }
        scanf("%d",&n);
        a=1;
        b=1;
        c++;
    }
    return 0;
}
				

