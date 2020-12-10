// Problem: 1271
// Solution: 1984482
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1392KB





						
#include <stdio.h>

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int m,
            n,
            k,
            a,
            b,
            x[200]={0},
            y[200]={0},
            tu[200][200]={0};
        scanf("%d %d %d",&m,&n,&k);


        int i;
        for(i=0;i<k;i++)
        {
            scanf("%d %d",&a,&b);
            a--;
            b--;
            x[a] = 1;
            y[b] = 1;
        }


        for(i=0;i<m;i++)
        {
            if(!x[i])
            {
                int i1;
                for(i1=0;i1<n;i1++)
                {
                    tu[i][i1] = 1;
                }
            }
        }


        for(i=0;i<n;i++)
        {
            if(!y[i])
            {
                int i1;
                for(i1=0;i1<m;i1++)
                {
                    tu[i1][i] = 1;
                }
            }
        }


        int j,
            sum=0;

        for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++)
            {
                if(tu[i][j]){
                    sum++;
                }
            }
        }


        printf("%d\n",sum);
    }
    return 0;
}


				

