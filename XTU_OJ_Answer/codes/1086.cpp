// Problem: 1086
// Solution: 1983829
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1288KB





						
#include <stdio.h>
#include <math.h>
int main()
{
    double a;
    scanf("%lf",&a);
    double result;
    if(a<0)
        result = 0;
    else if(a<=1)
        result = a*a;
    else if(1)
        result = sqrt(a);
    printf("%g\n",result);
    return 0;
}
				

