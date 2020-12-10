// Problem: 1255
// Solution: 1871149
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1168KB





						
#include <stdio.h>
#include <math.h>
int main()
{
    int n,a,b,c,d,e,f,g;
    double z;
    scanf("%d",&n);//n是样例个数
    for(z=1; n>0; n--)
    {
        scanf("%d %d",&a,&b);//ab是输入的两条边长
        if (a<b)
        {
            a=a+b;
            b=a-b;
            a=a-b;
        }//该if确保a为较大的数
/*第三边作为斜边*/        c=a*a+b*b;
        z=sqrt(c);
        d=z;
        e=c-d*d;//e=0时第三边为整数
 /*第三边作为直角边*/       c=a*a-b*b;
        z=sqrt(c);
        g=z;
        f=c-g*g;//f=0时第三边为整数
        if (f==0&&a!=b)
        {
            printf("%d\n",g);
        }
        else
        {
            if (e==0&&a!=b)
            {
                printf("%d\n",d);
            }
            else
                printf("None\n");
        }
    }
    return 0;
}

				

