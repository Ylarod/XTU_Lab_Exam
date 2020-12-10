// Problem: 1150
// Solution: 1960717
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1256KB





						
#include <stdio.h>
int f[12];
int main()
{
    int i,n,k,z[12];
    f[0] = 1;
    for(i=1;i<10;i++){
        f[i] = f[i-1]+1;
    }
    while(scanf("%d",&n)!=EOF){
            if(n==0){
                printf("0\n");
                continue;
            }
        for(i=1;n;i++){
            z[i] = n%f[i];
            n /= f[i];
        }
        for(i--;i;i--)printf("%d",z[i]);
        printf("\n");
    }
    return 0;
}

				

