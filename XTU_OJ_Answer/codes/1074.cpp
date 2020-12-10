// Problem: 1074
// Solution: 1979284
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1252KB





						
#include <stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    int sum = 0,m;
    while(n--)
    {
        scanf("%d",&m);
        sum += m;
    }
    printf("%d",sum);
}

				

