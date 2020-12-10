// Problem: 1295
// Solution: 1962685
// Language: G++
// Result: Accepted
// Time: 156MS
// Memory: 1252KB





						
#include <stdio.h>
int sushu(int a)
{
    int i;
    if(a==1)
    return 0;
    for(i=2;i*i<=a;i++)
    {//printf("进入循环\n");
        if(a%i==0)
            return 0;
    }
    return 1;
}
int poww(int a,int b)
{
    int result=1,i;
    for(i=0;i<b;i++)
    {
        result *= 10;
    }
    return a*result;
}
int judge (int a)
{
    int b,d,x,y,i,j,k,n,sum,result=0;
    n = a%10;
    if(n==0||n==1||(n==2&&a>10)||n==4||(n==5&&a>10)||n==6||n==8||n==9)
    return 0;
    else
    {//printf("ceshi0\n");
    //printf("%d",a);
        for(i=0;a>0;i++)
        {
            b = a%10;
         //   printf("fgdgd0\n");
            if(b==0)

                return 0;
              //  printf("dsgds1\n");
            a /= 10;
            //printf("ceshi1");
            result += poww(b,i);
          //  printf("%d\n",i);
          //printf("判断结果%d",sushu(result));
;            if(sushu(result)==0)
                return 0;
        }
      //  printf("ceshi2");
        return 1;
    }
}
int main()
{
    int k;
    scanf("%d",&k);
    while(k--)
    {
        int n;
        scanf("%d",&n);
        if(judge(n)) printf("Yes\n");
        else printf("No\n");
    }
}

				

