// Problem: 1275
// Solution: 1966519
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1256KB





						
#include<stdio.h>
int b[13][14]={0},T;
int shuchu(int i,int j)
{
    if(i==1) printf("Mon ");
    if(i==2) printf("Tue ");
    if(i==3) printf("Wen ");
    if(i==4) printf("Thur ");
    if(i==5) printf("Fri ");
    printf("%d %d\n",j-T+1,j);
    return 0;
}
int main()
{
    int K;
    scanf("%d",&K);
    getchar();
    while(K--)
    {
        int N,zs=0;
        scanf("%d %d",&N,&T);
        getchar();
        int c,d,i,j,a[13][14]={0},sum=0;
        for(i=0;i<9;i++)
            for(j=0;j<13;j++)
            {
                a[i][j]=1;
                b[i][j]=0;
            }
        char z[10];
        while(N--)
        {
            c = 0;
            d = 0;
            i = 0;
            scanf("%s %d %d",z,&c,&d);
            getchar();
            if(z[0]=='M') i = 1;
            if(z[0]=='T'&&z[1]=='u') i = 2;
            if(z[0]=='W') i = 3;
            if(z[0]=='T'&&z[1]=='h') i = 4;
            if(z[0]=='F') i = 5;
            if(z[0]=='S'&&z[1]== 'a') i = 6;
            if(z[0]=='S'&&z[1]=='u') i = 7;
            for(j=c;j<=d;j++)
                a[i][j] = 0;
        }
        for(i=1;i<6;i++)
        {
            sum = 0;
            for(j=1;j<5;j++)
            {
                if(a[i][j])
                {
                    sum++;
                    if(sum>=T)
                    {
                         b[i][j]=1;
                         zs++;
                    }
                }else{
                    sum = 0;
                }
            }
            sum = 0;
            for(j=5;j<9;j++)
            {
                if(a[i][j])
                {
                    sum++;
                    if(sum>=T)
                    {
                         b[i][j]=1;
                         zs++;
                    }
                }else{
                    sum = 0;
                }
            }
             sum = 0;
            for(j=9;j<12;j++)
            {
                if(a[i][j])
                {
                    sum++;
                    if(sum>=T)
                    {
                         b[i][j]=1;
                         zs++;
                    }
                }else{
                    sum = 0;
                }
            }
        }
        printf("%d\n",zs);
       /* for(i=1;i<8;i++){
            for(j=1;j<12;j++)
                printf("%d ",a[i][j]);
            printf("\n");
        }
        for(i=1;i<8;i++){
            for(j=1;j<12;j++)
                printf("%d ",b[i][j]);
            printf("\n");
        }*/
        for(i=1;i<6;i++)
        {
            for(j=2;j<12;j++)
            {
                if(b[i][j])
                    shuchu(i,j);
            }
        }
    }
    return 0;
}
				

