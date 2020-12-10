// Problem: 1236
// Solution: 1956724
// Language: G++
// Result: Accepted
// Time: 30MS
// Memory: 1252KB





						
#include <stdio.h>
int cifang(int a){
    int result=1;
    while(a--){
        result *= 2;
    }
    return result;
}
int main()
{
    int a[1000];
    int i;
    a[0] = 1;
    a[1] = 2;
    for(i=2;i<50&&a[i-1]<1000000;i++){
        a[i] = a[i-1]+a[i-2];
     //   printf("a[%d]:%d\n",i,a[i]);
    }
    int k;
    scanf("%d",&k);
    while(k--){
            int n,sum=0;
            scanf("%d",&n);
        for(i=28;i>=0;i--){
            if(a[i]<=n){
                n = n-a[i];
                sum += cifang(i);
            }
        }
        printf("%d\n",sum);
    }


}

				

