// Problem: 1108
// Solution: 1952959
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1248KB





						
#include<stdio.h>
#include<string.h>
int change(char str[],int t) //传入字符串与该字符串对应的进制 
{
    int i=0;
    int result=0;//存储结果 
    int flag=1;//用来做符号标记 
    int m=strlen(str); //数字串长度 
    if(str[0]=='-')  //字符串首位为-，说明为负数 
    {
        flag=-1;
        i++;
    }
    for(;i<m;i++)
    {
        int j;
        if(str[i]>='0'&&str[i]<='9') //数字字符转化为数字 
        {
            j=str[i]-'0';
        }
        else if(str[i]>='A'&&str[i]<='Z') //题目说使用A-Z依次表示10到35
        {
            j=str[i]-'A'+10;
        }
        else if(str[i]>='a'&&str[i]<='z') //题目说a-z表示36-61 
        {
            j=str[i]-'a'+36;
        }
        result=result*t+j; //进制公式 
    }
    return flag*result;
}
int main()
{
    int n;
    scanf("%d",&n);
    while(n--)
    {
        int a,b,Ta,Tb;
        char x[100],y[100];
        scanf(" %s %d %s %d",x,&Ta,y,&Tb);
        a=change(x,Ta); //调用函数 
        b=change(y,Tb); //调用函数 
        printf("%d\n",a+b);
    }
    return 0;
}
				

