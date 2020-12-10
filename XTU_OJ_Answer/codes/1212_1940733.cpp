// Problem: 1212
// Solution: 1940733
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1128KB





						
#include<stdio.h>
int main()
{
    int i,n,j,l;
    while(scanf("%d",&n)!=EOF&&n!=0)
    {for(i=1;i<=n;i++)
            {for(j=1;j<=(n-i);j++)printf(" ");
            for(l=1;l<i;l++)printf("%d",l);
            if(i!=1)printf("+");
            else printf("1");
            for(l=i-1;l>=1;l--)printf("%d",l);
            printf("\n");}}
    return 0;
 }

				

