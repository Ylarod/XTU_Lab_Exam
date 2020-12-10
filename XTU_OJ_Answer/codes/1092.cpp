// Problem: 1092
// Solution: 1979334
// Language: G++
// Result: Accepted
// Time: 30MS
// Memory: 1252KB





						
#include <stdio.h>
int main()
{
    int a,b;
    scanf("%d %d",&a,&b);
    if(a<0)
    {
        while(a<0)
            a += b;
    }
    printf("%d\n",a%b);
}

				

