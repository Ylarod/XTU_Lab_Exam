// Problem: 1296
// Solution: 1915051
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
        int a,b,n,m;
scanf("%d %d",&a,&b);
a--;
n=a/6*2;
m=a%6;
if(m<5&&m>0)n += 1;
if(a%6==5)n += 2;
a=b/6*2;
m=b%6;
if(m<5&&m>0)a += 1;
if(b%6==5)a += 2;
printf("%d\n",a-n);
}
return 0;
}
				

