// Problem: 1115
// Solution: 1952324
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1252KB





						
#include<stdio.h>
#include<string.h>
int main()
{
    int n,a,b,k,i,o,m;
    char str[201]={0};
    scanf("%d",&n);
    while(n--)
    {
        scanf("%s",str);
        k=strlen(str);
        scanf("%d%d",&a,&b);
         o=a-1+b/2;
        int t=0;
        m=1;
        for(i=a-1;i<o;i++)
        {
            if(str[i]==str[a+b-t-2]) m=1;
            else
            {
                m=0;
                break;
            }
            t++;
        }
        if(m==1) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}

				

