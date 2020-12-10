// Problem: 1281
// Solution: 1978499
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1244KB





						
#include <stdio.h>
#include <string.h>
int main()
{
    char a[205];
    while(gets(a)!=NULL)
    {
        int lena;
        lena = strlen(a);
        int judge=0,flag=1;
        int i;
        int ch[300]={0};
        for(i=0;i<lena;i++)
        {
            ch[a[i]]++;
        }
        for(i=65;i<=90;i++)
        {
            if(ch[i]||ch[i+32])
                judge++;
        }
        if(ch[32]>9||judge>10)
        {
            flag = 0;
        }
        if(flag)
            printf("Yes\n");
        else
            printf("No\n");
    }
}

				

