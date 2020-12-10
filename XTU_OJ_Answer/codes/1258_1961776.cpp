// Problem: 1258
// Solution: 1961776
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1256KB





						
#include<stdio.h>
#include<math.h>
void shuchu(int n,int m,char c,int x,int y,int str[])
{
    int i,j,k;
    int tmp;
    if(c=='L')
    {
        for(j=0; j<y; j++)
        {
            tmp=str[(x-1)*n];
            for(i=(x-1)*n+1; i<=(x-1)*n+n-1; i++)
            {
                str[i-1]=str[i];
            }
            str[(x-1)*n+n-1]=tmp;
        }
    }
    else if(c=='R')
    {
        for(j=0; j<y; j++) {
            tmp=str[(x-1)*n+n-1];
            for(i=(x-1)*n+n-2; i>=(x-1)*n; i--)
            {
                str[i+1]=str[i];
            }
            str[(x-1)*n]=tmp;
        }
    }
    else if(c=='U')
     {
        for(j=0; j<y; j++)
        {
            tmp=str[x-1];
            for(i=x+n-1; i<=n*n-n+x-1; i=i+n)
            {
                str[i-n]=str[i];
            }
            str[n*n-n+x-1]=tmp;
        }
    }
    else if(c=='D')
    {
        for(j=0; j<y; j++) {
            tmp=str[n*n-n+x-1];
            for(i=n*n-n-n+x-1; i>=x-1; i=i-n)
            {
                str[i+n]=str[i];
            }
            str[x-1]=tmp;
        }
    }
}
int main()
{
    int n,m;
    int i,T,x,y,c;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        getchar();
        int str[n*n];
        for(i=0; i<n*n; i++)
            str[i]=i+1;
        for(i=0; i<m; i++)
        {
            scanf("%c %d %d",&c,&x,&y);
            getchar();
            shuchu(n,m,c,x,y,str);
        }
        for(i=0; i<n*n; i++) {
            if(i!=n*n-1)
                  printf("%d ",str[i]);
            else
                  printf("%d",str[i]);
        }
        printf("\n");
    }
    return 0;
}

				

