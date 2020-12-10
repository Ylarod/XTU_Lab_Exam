// Problem: 1194
// Solution: 1963247
// Language: G++
// Result: Accepted
// Time: 30MS
// Memory: 8180KB





						
#include<stdio.h>
const int N = 1001;
const int mod = 1000000007;
long long d[1001], c[1001][1001];
int main()
{
    int i,j;
    //求错排
    d[2] = 1;
    for( i = 3; i < N; i ++)
        d[i] = (i - 1) * (d[i-1] + d[i-2]) % mod;
    //求组合数

//    printf("d1:%d",d[1]);
    for( i = 1; i < N; i ++)
        c[i][0] = c[i][i] = 1;
    for( i = 2; i < N; i ++)
        for( j = 1; j < i; j ++)
            c[i][j] = (c[i-1][j-1] + c[i-1][j]) % mod;
    int n, k;
    while(~scanf("%d%d", &n, &k), n + k)
        if(!k)
            printf("1\n"); //k为0时输出结果为1
        else
            printf("%I64d\n", d[k] * c[n][k] % mod);
    return 0;
}

				

