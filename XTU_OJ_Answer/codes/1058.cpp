// Problem: 1058
// Solution: 1979266
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1252KB





						
#include <stdio.h>
unsigned int gcd(unsigned int a,unsigned int b)
{
    unsigned int c;
    while(b)
    {
        a = a%b;
        c = a;
        a = b;
        b = c;
    }

    return a;
}
int main()
{
    unsigned int a,b,c,d;
    while(scanf("%d %d %d",&a,&b,&c)&&(a!=0||b!=0||c!=0))
    {
        a = gcd(a,b);
        if(a==0)
            printf("No\n");
        else if(c%a==0)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}

				

