// Problem: 1113
// Solution: 1875413
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1160KB





						
#include <stdio.h>
int main()
{
int n,a,b,c,d;
int x,y;
scanf("%d",&n);
for(a=1;n>0;n--){
scanf("%d %d",&a,&b);
scanf("%d %d",&c,&d);
if(a<b){
a=a+b;
b=a-b;
a=a-b;
}
if(c<d){
    c=c+d;
    d=c-d;
    c=c-d;
}
x=c-b;
y=d-a;
if(x*y<=0)
    printf("Yes\n");
else
    printf("No\n");
//a%b£»
//printf("%d",a);
}
return 0;
}

				

