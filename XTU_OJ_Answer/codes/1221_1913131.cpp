// Problem: 1221
// Solution: 1913131
// Language: G++
// Result: Accepted
// Time: 46MS
// Memory: 1156KB





						
#include <stdio.h>
int main()
{/*蛐蛐大神保平安*/
   unsigned long n;
   int count=0,judge=0,x=0,k;
   scanf("%d",&k);
    while(k--)
    {
       scanf("%I64d",&n);
     // n=256*256*256*255-2+256*256*256;
    //  printf("%d",&n);
        while(n)
        {
            judge=n%2;
            n=n/2;
            if(judge==1)
            {
                count++;
            }
            else
            {
                if(x<count)
                    x=count;
                count=0;
            }
        }
        if(x<count)
            x=count;
        printf("%d\n",x);
        count=0;
        judge=0;
        x=0;
   }
    return 0;
}
				

