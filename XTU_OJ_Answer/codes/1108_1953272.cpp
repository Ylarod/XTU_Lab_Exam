// Problem: 1108
// Solution: 1953272
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1248KB





						
#include <stdio.h>
#include <string.h>
int zhuanhuan(char c[],int a,int b)
{
    int i=0,flag=1,sum=0;
    if(c[0]=='-')
    {
        flag = -1;
        i++;
    }
    for(;i<b;i++)
    {
        if(c[i]>='A'&&c[i]<='Z')c[i] = c[i]-'A'+10;
        else if(c[i]>='a'&&c[i]<='z')c[i] = c[i]-'a'+36;
        else if(c[i]>='0'&&c[i]<='9')c[i] = c[i]-'0';
        sum = sum*a+c[i];
    }
    return sum*flag;
}
int main()
{
    int a,b,k,lenx,leny;
    scanf("%d",&k);
    while(k--)
    {
        char x[100],y[100];
        int sum1,sum2;
        scanf("%s %d %s %d",&x,&a,&y,&b);
        lenx = strlen(x);
        leny = strlen(y);
        sum1 = zhuanhuan(x,a,lenx);
        sum2 = zhuanhuan(y,b,leny);
        printf("%d\n",sum1+sum2);
    }
}


				

