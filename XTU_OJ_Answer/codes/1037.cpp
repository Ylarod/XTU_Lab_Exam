// Problem: 1037
// Solution: 1980770
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1256KB





						
#include <stdio.h>
#include <string.h>
char a[2002];
int lena;
int judgeone()
{
    int i,j,count;
    lena = strlen(a);
    for(j=0;j<lena;j++)
    {
        count = 0;
        for(i=j+1;a[j]!=a[i]&&i<lena;i++)
        {
            if(a[j]!=a[i])
            {
                count++;
            }
        //    printf("%d:%c %d:%c\n",j,a[j],i,a[i]);
        }
        if(count%2==1&&a[i-1]==a[j])
        {
            return 0;
        }
    }
    return 1;
}
int judgetwo()
{
    int i,count[257]={0};
    for(i=0;i<lena;i++)
    {
        count[a[i]]++;
    }
    for(i=65;i<123;i++)
    {
        if(count[i]%2)
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    int k;
    scanf("%d",&k);
    getchar();
    while(k--)
    {
        scanf("%s",a);
        if(judgeone())
        {
            if(judgetwo())
            {
                printf("Yes\n");
            }else
            {
                printf("No\n");
            }
        }else{
            printf("No\n");
        }
    }
    return 0;
}

				

