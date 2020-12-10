// Problem: 1076
// Solution: 1881756
// Language: G++
// Result: Accepted
// Time: 171MS
// Memory: 1164KB





						
#include <stdio.h>
int main(){
    unsigned long n;
    int a,judge=1,i;
    scanf("%I64d",&n);
    while(n!=0){
        if(n==1){
            printf("No\n");
        }else{
            if(n==2||n==3||n==5||n==7){
                printf("Yes\n");
            }else{
                for(i=2;i*i<=n;i++){
                    judge=n%i;
                    if(judge==0){
                        break;
                    }
                }
                if(judge==0){
                    printf("No\n");
                }else{
                    printf("Yes\n");
                }
            }
        }
        scanf("%I64d",&n);
    }
    return 0;
}
				

