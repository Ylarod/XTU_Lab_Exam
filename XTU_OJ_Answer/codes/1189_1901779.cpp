// Problem: 1189
// Solution: 1901779
// Language: G++
// Result: Accepted
// Time: 46MS
// Memory: 1164KB





						
#include <stdio.h>
int main()
{
    int n,a,b,c,y,x,xt;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d%d%d",&a,&b,&c);
        if(c==1)
        {
            if(a==b&&b!=0) printf("0\n");
            else if(a==b&&b==0)
                printf("1\n");
            else
                printf("None\n");
        }
        else
        {
            if(a==0&&b==0)
                printf("None\n");
            else
            {
                x=(a-b*c)/(c-1);
                y=(a-b*c)%(c-1);
                if(x>=0&&y==0)
                    printf("%d\n",x);
                else printf("None\n");
            }
        }
    }
    return 0;
}
				

