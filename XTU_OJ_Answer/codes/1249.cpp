// Problem: 1249
// Solution: 1963889
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1232KB





						
#include <stdio.h>
int pd(int a)
{
    int i,j,k;
    for(i=2;i*i<=a;i++)
    {
            if(a%i==0)
            return 0;
    }
    return 1;
}
int cifang(int a)
{
    int result=1,i;
    for(i=0;i<a;i++)
    {
        result *= 10;
    }
    return result;
}
int main()
{
    int i,j,a[100]={0,2,3,5,7},b[100]={1,3,7,9},judge,cf;
    for(i=1;i<5;i++)
    {
       printf("%d %d\n",i,a[i]);
    }
    int sum=4;
    cf=1;
    while(sum<83){
//printf("²âÊÔ0\n");
    for(i=1;i<84;i++)
    {
        if(a[i]>cifang(cf-1)&&a[i]<cifang(cf)){
              //  printf("²âÊÔ1\n");
            for(j=0;j<4;j++)
            {
                judge = a[i]*10+b[j];
                if(pd(judge)){
                    sum++;
                    printf("%d %d\n",sum,judge);
                    a[sum] = judge;
                }
            }
        }
    }
    cf++;
    }
  return 0;
}

				

