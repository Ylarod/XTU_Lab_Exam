// Problem: 1296
// Solution: 1915050
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1156KB





						
#include <stdio.h>
int main()
{
int k;
scanf("%d",&k);
while(k--){
        int a,b,n;
scanf("%d %d",&a,&b);
a--;
n=a/6*2;
if(a%6<5&&a%6>0)n += 1;
if(a%6==5)n += 2;
a=b/6*2;
if(b%6<5&&b%6>0)a += 1;
if(b%6==5)a += 2;
printf("%d\n",a-n);
}
return 0;
}
				

