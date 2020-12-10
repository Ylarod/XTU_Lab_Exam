// Problem: 1089
// Solution: 1904235
// Language: G++
// Result: Accepted
// Time: 296MS
// Memory: 1172KB





						
#include<stdio.h>
#include<math.h>
int main(){
    int x,k,i,c;
    while(scanf("%d",&x)!=EOF){
        k=sqrt(x);
        for(i=2;i<=k;i++){
            for(c=0;x%i==0;c++){
                x/=i;
            }
            if(c==0) continue;
            if(c==1) printf("%d",i);
            else if(c>=1){
                printf("%d^%d",i,c);
            } 
            if(x!=1) putchar('*');
            else break;
        }
        if(x!=1) printf("%d",x);
        putchar('\n');
    }
}

				

