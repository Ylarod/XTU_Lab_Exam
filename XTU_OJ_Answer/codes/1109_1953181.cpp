// Problem: 1109
// Solution: 1953181
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1248KB





						
#include<stdio.h>
#include<string.h>
int main()
{
    int n,t;
    scanf("%d",&n);
    for(t=1;t<=n;t++)
    {
        int i,k,m,n,j;
        char common[201];
        char str[201];
        scanf("%d",&k);
        for(i=0;i<k;i++)
        {
            if(i==0)
            {
                scanf(" %s",common);
                n=strlen(common); 
            }
            else
            {
                scanf(" %s",str);    
                for(j=0;j<n;j++)
                {
                    if(str[j]!=common[j])
                    {
                        common[j]='\0';
                    }
                } 
            }
        }
        printf("Case %d: %s\n",t,common); 
    }
    return 0;
}

				

