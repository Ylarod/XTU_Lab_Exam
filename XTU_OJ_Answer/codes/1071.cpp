// Problem: 1071
// Solution: 1870737
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1184KB





						
#include <stdio.h>
#include <math.h>
int main ()
{
    double a,b,c,s;
    scanf("%lf %lf %lf",&a,&b,&c);
    if (a<b)
    {
        a=a+b;
        b=a-b;
        a=a-b;
    }
    if (a<c)
    {
        a=a+c;
        c=a-c;
        a=a-c;
    }
    if (b<c)
    {
        b=b+c;
        c=b-c;
        b=b-c;
    }
    if (a<b+c)
    {
        s=a+b+c;
        s=s/2;
        s=s*(s-a)*(s-b)*(s-c);
        s=sqrt(s);
          printf("%0.2lf",s);
    }
    else
    {
        printf("Not a triangle.");
    }
    return 0;
}

				

