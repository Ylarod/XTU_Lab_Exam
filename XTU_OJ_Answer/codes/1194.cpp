// Problem: 1194
// Solution: 1963198
// Language: G++
// Result: Accepted
// Time: 62MS
// Memory: 8216KB





						
#include<cstdio>  
using namespace std;  
const int N = 1001;  
const int mod = 1000000007;  
#define ll long long  
ll d[N], c[N][N];  
int main()  
{  
    //求错排  
    d[2] = 1;  
    for(int i = 3; i < N; i ++)  
        d[i] = (i - 1) * (d[i-1] + d[i-2]) % mod;  
    //求组合数  
    for(int i = 1; i < N; i ++)  
        c[i][0] = c[i][i] = 1;  
    for(int i = 2; i < N; i ++)  
        for(int j = 1; j < i; j ++)  
            c[i][j] = (c[i-1][j-1] + c[i-1][j]) % mod;  
    int n, k;  
    while(~scanf("%d%d", &n, &k), n + k)  
        if(!k)  
            printf("1\n"); //k为0时输出结果为1  
        else  
            printf("%I64d\n", d[k] * c[n][k] % mod);  
    return 0;  
}
				

