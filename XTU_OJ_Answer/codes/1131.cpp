// Problem: 1131
// Solution: 1939444
// Language: G++
// Result: Accepted
// Time: 125MS
// Memory: 5040KB





						
#include <stdio.h>
int hh[1000001]={0};
int main()
{
    int k;
    scanf("%d",&k);
   // while(k--){
        int m,x,n,sum=0;
    //    scanf("%d %d",&m,&n);
    m=100;
    n=1000000;
        for(;m<=n;m++){
                x = m;
             int count=0,a[100]= {0},i;
        for(i=0; x; i++)
        {
            a[i] = x%10;
            x /= 10;
        }//数码分离
        i--;//i的值为该数数码个数
        if(a[0]-a[1]<=0)
        {
         //   printf("No\n");
        }
        else
        {
            int xh,judge;
          //  printf("i%d\n",i);
            for(xh=1; xh<i; xh++)
            {
                judge = (a[xh-1]-a[xh])*(a[xh]-a[xh+1]);//judge为负则该处是转折点 为零则是平台
                if(judge<0) count++;
              //  printf("%d\n",count);
                if(judge==0)
                {
                //    printf("No\n");
                    break;
                }
            }
            if(judge!=0)
            {
                if (count==1)hh[m]=1;//printf("Yes\n");
              //  else printf("No\n");
            }
        }
        }
                int i;
        for(i=100;i<=1000000;i++){
            hh[i] = hh[i]+hh[i-1];
        }
        while(k--){
                 scanf("%d %d",&m,&n);
            sum = hh[n]-hh[m-1];
            printf("%d\n",sum);
    }
}

				

