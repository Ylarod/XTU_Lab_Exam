// Problem: 1212
// Solution: 1956962
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1252KB





						
#include <stdio.h>
int main()
{
    int n;
    while(scanf("%d",&n)&&n){
        int i,k,judge,a,b,hs=1;
        for(;hs<=n;hs++){
            for(i=0;i<n-hs;i++){
                printf(" ");
            }
            for(i=1;i<hs;i++){
            printf("%d",i);
            }
            if(hs==1)printf("1");
            else printf("+");
             for(i--;i>0;i--){
            printf("%d",i);
            }
            printf("\n");
        }
    }
}

				

