// Problem: 1171
// Solution: 1959341
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1248KB





						
#include <stdio.h>
int main()
{
    int n;
    while(scanf("%d",&n)&&n!=0){
        int a,b,c,d,i,x,y,z,sum;
        a = 1;
        b = 1;
        for(i=1;i<n;i++){
            x = b;
            y = a+b;
            a = x;
            b = y;
        }
        printf("%d\n",a+b);
    }
    return 0;
}

				

