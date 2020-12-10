// Problem: 1055
// Solution: 1912642
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1152KB





						
#include<stdio.h>
int main()
{
    char a[502]={0};
    int x,i,m,n;
        scanf("%s",&a);

         while(a[0]-48)
    {
        x=0;
        for(i=0;i<502;i++)
        {
        if(a[i]>48&&a[i]<58){
        a[i]=a[i]-48;
            x=a[i]+x;
            }
        }
        m=x;

        while(m>=10)
        {
            for(n=0;m!=0;)
        {
            n=m%10+n;
            m=m/10;
        }
        m=n;
        }
        printf("%d\n",m);
        scanf("%s",&a);
    }
}
				

