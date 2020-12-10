// Problem: 1257
// Solution: 1964196
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1252KB





						
#include <stdio.h>
int main()
{
    int c[40][40],i,j;
    for( i = 1; i < 34; i ++)
        c[i][0] = c[i][i] = 1;
    for( i = 2; i < 34; i ++)
        for( j = 1; j < i; j ++)
            c[i][j] = (c[i-1][j-1] + c[i-1][j]);
    int k;
    scanf("%d",&k);
    while(k--)
    {
        int m,n,a,b;
        scanf("%d %d",&n,&m);
        if((n-m)%2){
            printf("0\n");
            continue;
        }
        m = (n-m)/2;
        printf("%d\n",c[n][m]);
    }
    return 0;
}

				

