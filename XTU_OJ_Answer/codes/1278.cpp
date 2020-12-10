// Problem: 1278
// Solution: 1934285
// Language: G++
// Result: Accepted
// Time: 234MS
// Memory: 1160KB





						
#include <stdio.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--){
        int n,a[10002],i,judge,z,judgeone=1;
        scanf("%d",&n);
        for(i=0;i<n;i++){
         scanf("%d",&a[i]);
        }
        judge = a[1]-a[0];
        for(i=2;i<n;i++){
            z = a[i]-a[i-1];
            if(judge!=z){
                judgeone = 0;
                break;
            }
        }
        if(judgeone)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}

				

