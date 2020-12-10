// Problem: 1085
// Solution: 1857742
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1184KB





						
#include <stdio.h>
#include <math.h>
int main()
{
   double x,y,a,b,c,d,e;
   scanf ("%lf %lf %lf %lf",&a,&b,&c,&d);
  // d=n/180*c;
  // printf("%f",d);
  x=c-a;
  y=d-b;
   e=x*x+y*y;
   e=sqrt(e);
   printf("%g\n",e);
}

				

