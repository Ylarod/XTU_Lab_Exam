// Problem: 1108
// Solution: 1952959
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1248KB





						
#include<stdio.h>
#include<string.h>
int change(char str[],int t) //�����ַ�������ַ�����Ӧ�Ľ��� 
{
    int i=0;
    int result=0;//�洢��� 
    int flag=1;//���������ű�� 
    int m=strlen(str); //���ִ����� 
    if(str[0]=='-')  //�ַ�����λΪ-��˵��Ϊ���� 
    {
        flag=-1;
        i++;
    }
    for(;i<m;i++)
    {
        int j;
        if(str[i]>='0'&&str[i]<='9') //�����ַ�ת��Ϊ���� 
        {
            j=str[i]-'0';
        }
        else if(str[i]>='A'&&str[i]<='Z') //��Ŀ˵ʹ��A-Z���α�ʾ10��35
        {
            j=str[i]-'A'+10;
        }
        else if(str[i]>='a'&&str[i]<='z') //��Ŀ˵a-z��ʾ36-61 
        {
            j=str[i]-'a'+36;
        }
        result=result*t+j; //���ƹ�ʽ 
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
        a=change(x,Ta); //���ú��� 
        b=change(y,Tb); //���ú��� 
        printf("%d\n",a+b);
    }
    return 0;
}
				

