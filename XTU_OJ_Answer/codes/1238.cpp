// Problem: 1238
// Solution: 1960070
// Language: G++
// Result: Accepted
// Time: 46MS
// Memory: 16920KB





						
#include <stdio.h>
long long f[1000002],cifang[1000002];
int main()
{
    int k,i,mo=1000000007;
       f[1] = 0;
        f[2] = 1;
        f[3] = 3;
        cifang[1]=2;
        for(i=2;i<1000001;i++){
            cifang[i] = cifang[i-1]*2;
            cifang[i] = cifang[i]%mo;
        }
 //       printf("%d",&cifang[10045]);
        for(i=4;i<=1000000;i++){
            f[i] = f[i-1]+cifang[i-2]+f[i-2];
            f[i] = f[i]%mo;
           // if(i%30000==0)
            //printf("%d\n",i);
        }
    scanf("%d",&k);
    while(k--){
        int n;


        /*f[n]=f[n-1](最高为接0)+(最高位接1)2^(n-2)(1结尾的串）+f[n-2](最高位为0的串)*/

       // printf("测试");
        scanf("%d",&n);
        printf("%lld\n",f[n]);
    }
    return 0;
}

				

