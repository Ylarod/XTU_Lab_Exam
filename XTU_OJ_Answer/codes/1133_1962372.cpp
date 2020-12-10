// Problem: 1133
// Solution: 1962372
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1256KB





						
#include <stdio.h>
#include <string.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--)
    {
        char str[40][30]={0},i=0,j,k,sum[31]={0},sj,judge,p[30];
        while(scanf("%s",p),strcmp(p,"START")!=0);
        while(scanf("%s",p),strcmp(p,"END")!=0)
        {//puts(str[i]);
            strcpy(str[i],p);
            i++;
            for(j=i-2; j>=0; j--)
            {
                if(strcmp(str[j],str[i-1])==0)
                {
                    sum[j]++;
                }  //printf("sumj[%d]:%d sumk[%d]:%d\n",j,sum[j],k,sum[k]);
            }
        }
        sj = 0;
        for(j=1; j<i; j++)
        { //printf("sum[%d]:%d judge:%d sj:%d\n",j,sum[j],judge,sj);
            if(sum[j]>sum[sj]||(sum[j]==sum[sj]&&strcmp(str[j],str[sj])<0)) sj = j;
        }
        printf("%s\n",str[sj]);
    }
    return 0;
}

				

