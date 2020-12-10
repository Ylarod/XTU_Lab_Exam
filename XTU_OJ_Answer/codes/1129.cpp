// Problem: 1129
// Solution: 1939454
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1128KB





						
#include <stdio.h>
int jueduizhi(int a,int b){
if(a>b) a=a-b;
else a=b-a;
return a;
}
int main(){
    int k,x1,x2,y1,y2,a,b,sum;
    scanf("%d",&k);
    while(k--){
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
        a = jueduizhi(x1,x2);
        b = jueduizhi(y1,y2);
        sum = a+b;
        printf("%d\n",sum);
    }
}

				

