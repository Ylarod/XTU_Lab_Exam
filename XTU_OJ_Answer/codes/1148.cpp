// Problem: 1148
// Solution: 1959679
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1248KB





						
#include <stdio.h>
int main()
{
    int k;
    while(scanf("%d",&k)&&k!=0){
        int i,n,a[102],b,c,d,flag,judge,sum;
        n = k;
        while(k--){
            scanf("%d",&a[k]);
            //printf("a[%d]:%d",k,a[k]);
        }while(n>=1){
        for(i=0;i<n-1;i++){
            a[i] = (a[i]+a[i+1])%2013;
        }
        n--;
        }
        printf("%d\n",a[0]);
    }
}

				

