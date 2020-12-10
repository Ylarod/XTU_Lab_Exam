// Problem: 1176
// Solution: 1970483
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1264KB





						
#include <stdio.h>
#include <string.h>
char team[20][20]={0},tem[20]={0};
int th[20]={0};
int shi[20]={0},fen[20]={0},miao[20]={0};
int kk[1200]={0};
int main()
{
    int zs;
    scanf("%d",&zs);
    int hour,min,s,num,n=1,i;
    char dui[30],zt[30];
    while(scanf("%d:%d:%d %s %d",&hour,&min,&s,dui,&num)!=EOF,gets(zt))
    {
        i = 1;
        if(zt[1]=='A')
        {
            for(i=1;i<n;i++)
            {
                if(th[i]==num)
                {
                    if(hour<shi[i])
                    {
                            shi[i] = hour;
                            fen[i] = min;
                            miao[i] = s;
                            strcpy(team[i],dui);
                    }else if(hour==shi[i])
                    {
                        if(min<fen[i])
                        {
                             shi[i] = hour;
                             fen[i] = min;
                             miao[i] = s;
                             strcpy(team[i],dui);
                        }else if(min==fen[i])
                        {
                            if(s<miao[i])
                            {
                                shi[i] = hour;
                                fen[i] = min;
                                miao[i] = s;
                                strcpy(team[i],dui);
                            }
                        }
                    }
                    break;
                }
            }
            if(i==n)
            {
                  //  printf("²âÊÔ3\n");
                th[n] = num;
                shi[n] = hour;
                fen[n] = min;
                miao[n] = s;
                strcpy(team[n],dui);
                n++;
            }
        }
    }
    for(i=1;i<n;i++)
    {
        kk[th[i]] = i;
    }
    for(i=1;i<=zs;i++)
    {
        if(kk[1000+i]==0)
        printf("%d\n",1000+i);
        else
        {
            printf("%d ",th[kk[i+1000]]);
            if(shi[kk[1000+i]]<10) printf("0");
            printf("%d:",shi[kk[1000+i]]);
            if(fen[kk[1000+i]]<10) printf("0");
            printf("%d:",fen[kk[1000+i]]);
            if(miao[kk[1000+i]]<10) printf("0");
            printf("%d ",miao[kk[1000+i]]);
            printf("%s\n",team[kk[1000+i]]);
        }
    }
    return 0;
}

				

