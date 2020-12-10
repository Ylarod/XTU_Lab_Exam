// Problem: 1078
// Solution: 1978560
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1256KB





						
#include <stdio.h>
int main()
{
    char ch,cas=1,i,j;
    while(scanf("%c",&ch)&&ch!='#')
    {
        getchar();
        printf("case %d:\n",cas);
        for(j=ch;j>64;j--)
        {
            for(i=ch-j;i>0;i--)
                printf(" ");
            for(i=65;i<j;i++)
                printf("%c",i);
            for(;i>64;i--)
                printf("%c",i);
            printf("\n");
        }
        cas++;
    }
    return 0;
}

				

