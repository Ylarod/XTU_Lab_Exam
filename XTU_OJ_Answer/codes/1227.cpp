// Problem: 1227
// Solution: 1965827
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1256KB





						
#include <stdio.h>
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n,zt=0,flagx=1,flagy=0,x=0,y=0;
        scanf("%d",&n);
        while(n--)
        {
            char a[10];
            int len;
            zt = (zt+4)%4;
            getchar();
            if(zt==0)
            {
                flagx = 0;
                flagy = 1;
            }
            if(zt==1)
            {
                flagx = 1;
                flagy = 0;
            }
            if(zt==2)
            {
                flagx = 0;
                flagy = -1;
            }
            if(zt==3)
            {
                flagx = -1;
                flagy = 0;
            }
            scanf("%s",a);
            if(a[0]=='R')
            {
                zt++;
            }
            if(a[0]=='L')
            {
                zt--;
            }
            if(a[0]=='B')
            {
                zt +=2;
            }
            if(a[0]=='F')
            {
                getchar();
                scanf("%d",&len);
                x += flagx*len;
                y += flagy*len;
            }
        }
        printf("%d %d\n",x,y);
    }
    return 0;
}

				

