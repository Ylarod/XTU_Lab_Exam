// Problem: 1072
// Solution: 1876389
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1180KB





						
#include <stdio.H>
#include <math.h>
int main()
{
double x,y;
scanf("%lf",&x);
if(x>=0&&x<30){
if(x>=20){
y=cos(x+4.0);
y=y*y*y*y;}
if(x<10){
y=cos(x+3.0);}
if(x>=10&&x<20){
y=cos(x+7.5);
y=y*y;}
printf("%0.5f",y);
}else{
printf("Not define");
}
return 0;
}

				

