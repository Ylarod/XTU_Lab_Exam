// Problem: 1059
// Solution: 1885770
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1160KB





						
#include <stdio.h>
int main()
/*蛐蛐大神保平安*/
{
    int count=0,judge,judgetwo=0,n,x;
    while(x=scanf("%d",&n)==1){
    if(n<0){
        n=0-(n+1);
        judgetwo=1;
    }
    while(n){
        judge=n%2;
        n=n/2;
        if(judge==1)
            count++;
    }
    if(judgetwo==1)
        count=32-count;
    printf("%d\n",count);
    judgetwo=0;
    count=0;}
return 0;
}

				

