// Problem: 1194
// Solution: 1963248
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 8180KB





						
#include<stdio.h>
long long d[1001], c[1001][1001];
int main()
{
    int i,j,N=1001,mod = 1000000007;
    d[2] = 1;
    for( i = 3; i < N; i ++)
        d[i] = (i - 1) * (d[i-1] + d[i-2]) % mod;
    for( i = 1; i < N; i ++)
        c[i][0] = c[i][i] = 1;
    for( i = 2; i < N; i ++)
        for( j = 1; j < i; j ++)
            c[i][j] = (c[i-1][j-1] + c[i-1][j]) % mod;
    int n, k;
    while(~scanf("%d%d", &n, &k), n + k)
        if(!k)
            printf("1\n"); 
        else
            printf("%I64d\n", d[k] * c[n][k] % mod);
    return 0;
}

				

