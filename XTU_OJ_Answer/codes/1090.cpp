// Problem: 1090
// Solution: 1938766
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1128KB





						
#include <stdio.h>
int main()
{
    int k;
        int n,x,y,z,i,j,count,judge;
        int a[35][35];
        for(i=1;i<=34;i++){
            a[i][1] = 1;
            for(j=2;j<i;j++){
                a[i][j] = a[i-1][j]+a[i-1][j-1];
            }
            a[i][i] = 1;
        }
        scanf("%d",&n);
        while(n>=0){
        if(n==0){
            printf("2^0=1\n");
            scanf("%d",&n);}
        else{
        printf("2^%d=1",n);
        n++;
        for(j=2;j<=n;j++){
            printf("+%d",a[n][j]);
        }
        printf("\n");
         scanf("%d",&n);
        }
    }
    return 0;
}

				

