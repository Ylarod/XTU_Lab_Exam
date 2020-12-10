// Problem: 1139
// Solution: 1916386
// Language: G++
// Result: Accepted
// Time: 187MS
// Memory: 1156KB





						
#include <stdio.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--){
        int i,x,count=0,judge=0,m=0;
        scanf("%d",&x);
        for(i=2;i*i<=x;){
            if(x%i==0){
                count++;
                x=x/i;
            }else{
                i++;
            }
        }
        if(count==1&&i!=x){
           printf("Yes\n");
        }else{
        printf("No\n");
        }
    }
    return 0;
}
				

