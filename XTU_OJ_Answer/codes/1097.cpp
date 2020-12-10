// Problem: 1097
// Solution: 1939308
// Language: G++
// Result: Accepted
// Time: 46MS
// Memory: 1128KB





						
#include <stdio.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--){
        int n,a[1002],i,judge=1,cao;
        char ch;
        scanf("%d %c",&n,&ch);
         i = n;
        cao=ch;
        while(n--){
            scanf("%d",&a[n]);
        }
        n=i;
        while(judge){
                judge = 0;
            for(i=0;i<n-1;i++){
                if(a[i]>a[i+1]){
                a[i] = a[i]+a[i+1];
                a[i+1] = a[i]-a[i+1];
                a[i] = a[i]-a[i+1];
                judge = 1;
                }
            }
        }

        if(cao==65){
           for(i=0;i<n;i++){
                printf("%d",a[i]);
           if(i<n-1)printf(" ");}
           printf("\n");
        }else{
            for(n--;n>=0;n--){printf("%d",a[n]);
            if(n)printf(" ");
            }
              printf("\n");
        }
    }
}

				

