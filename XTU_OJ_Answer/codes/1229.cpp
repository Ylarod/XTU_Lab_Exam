// Problem: 1229
// Solution: 1966239
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1248KB





						
#include <stdio.h>
int main()
{
    char a[12];
    while(scanf("%s",a)!=EOF)
    {
        int biaozhi,i,j,sum=0;
        for(i=0;i<10;i++)
        {
            if(a[i]>47&&a[i]<58)
            {
                sum += (a[i]-48)*(10-i);
            }else if(a[i]=='X')
            {
                sum += 10;
            }
            else{
                biaozhi = i;
            }
        }
        j = sum%11;
        if(j==0) a[biaozhi] = 48;
        else
        {
            for(i=1;i<11;i++)
            {
               // printf("%d\n",i);
                if((j+(10-biaozhi)*i)%11==0)
                    break;
            }
            if(i==10)
                a[biaozhi] = 88;
            else
                a[biaozhi] = i+48;
        }
        puts(a);
    }
    return 0;
}

				

