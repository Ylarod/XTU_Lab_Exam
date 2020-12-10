// Problem: 1294
// Solution: 1914199
// Language: G++
// Result: Accepted
// Time: 671MS
// Memory: 1164KB





						
#include <stdio.h>
int main()
{
char a[10001];
int a1,a2,n,k,i,count;
scanf("%d",&k);
while(k--){
scanf("%s",&a);
scanf("%d",&n);
while(n--){
scanf("%d %d",&a1,&a2);
for(i=a1-1,count=0;i<a2-1;i++){
if(a[i]!=a[i+1])count++;
}
printf("%d\n",count);
}
}
return 0;
}

				

