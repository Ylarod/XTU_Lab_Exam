// Problem: 1296
// Solution: 1974480
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1256KB





						
#include <stdio.h>
int zhuanhuan(int a)
{
if(a%6==0)
return a/6*2;
if(a%6<5)
return a/6*2+1;
if(a%6==5)
return a/6*2+2;
}
int main()
{
   int k;
scanf("%d",&k);
while(k--)
{
int a,b;
scanf("%d %d",&a,&b);
a = zhuanhuan(a-1);
b = zhuanhuan(b);
printf("%d\n",b-a);
}
return 0;
}

				

