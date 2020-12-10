// Problem: 1149
// Solution: 1960745
// Language: G++
// Result: Accepted
// Time: 93MS
// Memory: 1328KB





						
#include <stdio.h>
int main()
{
    int a,b,c;
    while(scanf("%d %d %d",&a,&b,&c)!=EOF){
        int i,x,y,z,sum,judge=1;
        int m[10001]={0};
        int n[10001]={0};
        for(i=1;i<=c;i++){
            n[i] = (a*n[i-1]+b)%c;
        }
         for(i=1;i<=c;i++){
           m[n[i]] = 1;
           //printf("m[%d]:%d\n",n[i],m[n[i]]);
        }
         for(i=1;i<c;i++){
            if(m[i]==0) judge = 0;
        }
        if(judge) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
/*线性同余随机数发生器是按Xn+1 = (aXn+c)%m 产生的，其中X0=0。 我们希望能产生所有的0~m-1的数，现在给你一系列的a,c,m,请计算一下是否能产生所有的0~m-1的数。

输入
有多组样例，每个样例一行，为三个整数，a(1≤a;≤10,000),c(0≤c≤100,000),m(1≤m≤10,000)。

输出
每行输出一个样例的结果，如果能产生所有0~m-1的数，输出Yes，否则输出No。

样例输入
1 2 7
2 3 5

样例输出
Yes
No*/

				

