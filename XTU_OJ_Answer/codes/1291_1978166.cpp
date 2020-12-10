// Problem: 1291
// Solution: 1978166
// Language: G++
// Result: Accepted
// Time: 109MS
// Memory: 1252KB





						
#include <stdio.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--)
    {
        int n,m;
        scanf("%d %d",&n,&m);
        int jiage[1002];
        int i;
        for(i=0;i<n;i++)
            scanf("%d",&jiage[i]);//
        int judge=1;
        while(judge)
        {
            judge = 0;
            for(i=0;i<n-1;i++)
            {
                if(jiage[i]<jiage[i+1])
                {
                    int c;
                    c = jiage[i];
                    jiage[i] = jiage[i+1];
                    jiage[i+1] = c;
                    judge = 1;
                }
            }
        }
        judge = jiage[0]-jiage[m-1];
        int he=0,hee=0,j;
        for(j=0;j<m;j++)
            he += jiage[j];
        for(i=1;i<n-m+1;i++)
        {
            hee = 0;
            if(judge==jiage[i]-jiage[i+m-1])
            {
                for(j=i;j<i+m;j++)
                    hee += jiage[j];
                if(he>hee)
                {
                    he = hee;
                }
            }else if(judge>jiage[i]-jiage[i+m-1])
            {
                judge=jiage[i]-jiage[i+m-1];
                for(j=i;j<i+m;j++)
                    hee += jiage[j];
                he = hee;
            }
        }
        printf("%d %d\n",judge,he);
    }
    return 0;
}

				

