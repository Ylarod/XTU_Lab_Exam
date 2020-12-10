// Problem: 1211
// Solution: 1956952
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1248KB





						
#include <stdio.h>
int main ()
{
    int k;
    scanf("%d",&k);
    while(k--){
        int a,b,c;
        scanf("%d+%d=%d",&a,&b,&c);
        if(a+b==c) printf("Yes\n");
        else printf("No\n");
    }
}

				

