// Problem: 1084
// Solution: 1857719
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1184KB





						
#include <stdio.h>
#include <math.h>
int main()
{
   double n=3.1415926,a,b,c,d,e;
   scanf ("%lf %lf %lf",&a,&b,&c);
   d=n/180*c;
  // printf("%f",d);
   e=a*a+b*b-2*cos(d)*a*b;
   e=sqrt(e);
   printf("%g\n",e);
}

				

