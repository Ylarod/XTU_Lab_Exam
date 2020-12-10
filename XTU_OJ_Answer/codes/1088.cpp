// Problem: 1088
// Solution: 1849823
// Language: G++
// Result: Accepted
// Time: 734MS
// Memory: 1164KB





						
#include<stdio.h>

int main(void)
{
    int n,i,result;
    while((1 == scanf("%d",&n)) && -1 != n)
    {
         result = 1;
         for(i=1;i<=n;i++)
         {
              result = result * i % 10007;
         }
         
         printf("%d\n",result);
    }
    return 0;
}
				

