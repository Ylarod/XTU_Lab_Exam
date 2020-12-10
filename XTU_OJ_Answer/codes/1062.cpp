// Problem: 1062
// Solution: 1866980
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1164KB





						
#include <stdio.h>
int main()
{
char n;
 //   do
  //    {
          scanf("%c",&n);
        if (n>=65&&n<=90)
            n=n+32;
        else
            if(n>=97&&n<=122)
            n=n-32;
        printf("%c",n);
   //          }while (1<2);
   return 0;
}


				

