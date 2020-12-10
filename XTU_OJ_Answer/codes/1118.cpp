// Problem: 1118
// Solution: 1875734
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1164KB





						
#include <stdio.h>
int main()
{
int n,a,b,c,d;
scanf("%d",&n);
for(;n>0;n--){
scanf("%d %d %d",&a,&b,&c);
if(a==0&&b==0){
if(c==0)
printf("INF\n");
else
printf("0\n");
}else{
if(a==0){
    printf("1\n");
}else{
d=b*b-4*a*c;
if(d<0)
printf("0\n");
if(d==0)
printf("1\n");
if(d>0)
printf("2\n");
}
}
}
return 0;
}

				

