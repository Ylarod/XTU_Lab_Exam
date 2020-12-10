// Problem: 1101
// Solution: 1870853
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1160KB





						
#include <stdio.h>
int main()
{
char a[201];
int n,i=0;
scanf("%d",&n);
getchar ();
do{
gets(a);
for (i=0;a[i]!='\0';i++){
if(a[i]>='A'&&a[i]<='Z')
a[i]+=32;
else
if(a[i]>='a'&&a[i]<='z')
a[i]-=32;
}puts(a);
n--;
}while(n>0);
return 0;
}

				

