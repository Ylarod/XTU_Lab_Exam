// Problem: 1251
// Solution: 1879664
// Language: G++
// Result: Accepted
// Time: 46MS
// Memory: 1164KB





						
#include <stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    while(n--)
    {
        int a,b,count=0;
        scanf("%d",&a);
        b=a;
        if(a>20)
        {
            while(b)
            {
                b=b/10;
                count++;
            }
            b=a-9*count;
        }
        else
        {
            b=1;
        }
        int he,zheng,yu,judge=1;
        for(he=0; b<a; b++)
        {
            he=0;
            zheng=b;
            while(zheng)
            {
                yu=zheng%10;
                he=he+yu;
                zheng=zheng/10;
            }
         
            he=he+b;
            he=a-he;
        
            if(he==0)
            {
                judge=0;
                break;
            }
        }
        if(judge==1)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }
    return 0;
}

				

