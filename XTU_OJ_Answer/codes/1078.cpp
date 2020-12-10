// Problem: 1078
// Solution: 1876428
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1164KB





						
#include <stdio.h>
int main()
{
    char a;
//scanf("%c",&a);
    int counta=1,countb=1,n=1,b;
    while(a!='#')
    {
        scanf("%c",&a);
        if(a=='#')
            break;
        printf("case %d:\n",n);
        countb=1;
        while(a>64)
        {
            for(counta=1; counta<countb; counta++)
            {
                printf(" ");
            }
            for(b=65; b<=a; b++)
            {
                printf("%c",b);
            }
            b--;
            b--;
            for(; b>64; b--)
            {
                printf("%c",b);
            }
            printf("\n");
            a--;
            countb++;
        }
        n++;
//printf("%d",n);
        getchar();
    }
}


				

