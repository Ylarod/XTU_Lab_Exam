// Problem: 1056
// Solution: 1979251
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1256KB





						
#include <stdio.h>
int main()
{
    int n,m,a[30],b[10],c[10];
    while(scanf("%d",&n)&&n)
    {
        scanf("%d",&m);
        int i=0;
        while(n)
        {
            b[i] = n%10;
            n /= 10;
            i++;
        }
      //  printf("ceshi\n");
        for(i=0;i<m;i++)
        {
            scanf("%d",&a[i]);
        }
        //printf("ceshi1\n");
        for(i=0;i<m;i++)
        {
            int j=0;
            while(a[i])
            {
                c[j] = a[i]%10;
                a[i] /= 10;
                j++;
            }
           //printf("ceshi2\n");
            int k,x=0,y=0;
            for(k=0;k<4;k++)
            {
              //  printf("%d %d    ",c[k],b[k]);
                for(j=0;j<4;j++)
                {
                    if(c[k]==b[j])
                    {
                        if(k==j)
                            x++;
                        else
                            y++;
                    }
                }
            }
         //   printf("FT\n");
            printf("%dA%dB",x,y);
            if(i<m-1)
                printf(" ");
            else
                printf("\n");
        }
    }
    return 0;
}

				

