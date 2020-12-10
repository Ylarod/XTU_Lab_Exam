// Problem: 1231
// Solution: 1876930
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1160KB





						
#include <stdio.h>
int main()
{
int n,x,y;
scanf("%d",&n);
while(n--){
scanf("%d",&x);
if(x<100)
y=3*x-100;
else
y=2*x;
printf("%d\n",y);
}
return 0;
}
				

