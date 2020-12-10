// Problem: 1057
// Solution: 1871305
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1164KB





						
#include <stdio.h>
int main ()
{
int n,i,lie,hang,a=1;
scanf("%d",&n);
while (n!=0){
hang=3*n;
lie=n;
printf("Case %d:\n",a);
while (hang!=0){
do{
printf("XTU");
n--;
}while (n>0);
printf("\n");
n=lie;
hang--;
}
printf("\n");
scanf("%d",&n);
a++;
}
return 0;
}

				

