// Problem: 1070
// Solution: 1870669
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1160KB





						
#include <stdio.h>
int main()
{
int a,b,c,n;
scanf("%d",&n);
c=n%10;
a=n/100;
b=n%100;
b=b/10;
if (a==b&&a==c){
printf("No");
}
else{
if (a!=b&&a!=c&&b!=c)
printf("No");
else
printf("Yes");
}
return 0;
}

				

