// Problem: 1100
// Solution: 1848502
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1180KB





						
#include <stdio.h>
 int main()
 {
     int h,a,b;
     double s;
     scanf("%d",&h);
     do{
         scanf("%d %d",&a,&b);
         h--;
         s=a*b;
         s=s/2;
         printf("%0.1lf\n",s);
         }
         while (h>0);
     }
				

