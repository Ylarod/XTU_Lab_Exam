// Problem: 1144
// Solution: 1876306
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1164KB





						
#include <stdio.h>
int main()
{
int n,a,b,c,d;
scanf("%d",&n);
while(n--){
scanf("%d %d %d",&a,&b,&c);
d=(a+a+b*c-b);
d=d*c;
d=d/2;
printf("%d\n",d);
}
}

				

