// Problem: 1267
// Solution: 1963540
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1252KB





						
#include <stdio.h>
char a[102],zz[12][12];
int huanhang(int n,int m,int x,int y)
{
    int i,j,c;
    for(i=0;i<m;i++)
    {
        c = a[(x-1)*m+i];
        a[(x-1)*m+i] = a[(y-1)*m+i];
        a[(y-1)*m+i] = c;
    }
    return 0;
}
int huanlie(int n,int m,int x,int y)
{
    int i,j,c;
    for(i=0;i<n;i++)
    {
        c = a[i*m+x-1];
        a[i*m+x-1] = a[i*m+y-1];
        a[i*m+y-1] = c;
    }
    return 0;
}
int zy(int n,int m)
{
    int i,j,k,b,x,y,c;
    for(j=1;j<=m/2;j++)
    {
        x = j;
        y = m-j+1;
        for(i=0;i<n;i++)
        {
            c = a[i*m+x-1];
            a[i*m+x-1] = a[i*m+y-1];
            a[i*m+y-1] = c;
        }
    }
    return 0;
}
int sx(int n,int m)
{
    int i,j,k,x,y,b,c;
    for(j=1;j<=n/2;j++)
    {
        x = j;
        y = n-j+1;
        for(i=0;i<m;i++)
    {
        c = a[(x-1)*m+i];
        a[(x-1)*m+i] = a[(y-1)*m+i];
        a[(y-1)*m+i] = c;
    }
    }
    return 0;
}
int zhuanzhi(int n,int m)
{
    int i,j,c;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {//printf("i:%d j:%d",i,j);
           // zz[i*m+j] = a[j*m+i];
            zz[j][i] = a[i*m+j];;
        }//printf("\n");
    }
    return 0;
}
int shuchu(int n,int m)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            if(j!=0) printf(" ");
            printf("%d",a[i*m+j]);
        }printf("\n");
    }printf("\n");
    return 0;
}
int main()
{
    int i,j,k,m,n,sum,judge,x,y;
    char b,c;
    for(i=0;i<101;i++) a[i] = i+1;
    while(scanf("%c%c",&b,&c)!=EOF)
    {
        if(b=='I'||b=='S')
        {
            scanf(" %d %d",&x,&y);
            getchar();
            if(c=='N')
            {
                n = x;
                m = y;
                for(i=0;i<101;i++) a[i] = i+1;
            }
            if(c=='R')
            {
                huanhang(n,m,x,y);
            }
            if(c=='C')
            {
                huanlie(n,m,x,y);
            }
        }else{
            getchar();
            if(b=='F')
            {
                if(c=='C')
                {
                    zy(n,m);
                }
                if(c=='R')
                {
                    sx(n,m);
                }
            }
            if(b=='T')
            {
                zhuanzhi(n,m);
                sum = n;
                n = m;
                m = sum;
                for(i=0;i<n;i++)
                {
                    for(j=0;j<m;j++)
                    {
                       a[i*m+j] = zz[i][j];
                    }
                }
            }
            if(b=='P')
            {
                shuchu(n,m);
            }
        }

    }
    return 0;
}

				

