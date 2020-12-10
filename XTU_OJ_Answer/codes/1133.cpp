// Problem: 1133
// Solution: 1962360
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1256KB





						
#include<stdio.h>
#include<string.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--)
    {
        char p[30];
        char str[30][30]={0};
        int num[30]={0};
        int i=0,j;
        while(scanf("%s",p),strcmp(p,"START")!=0);
        while(scanf("%s",p),strcmp(p,"END")!=0)
        {
            strcpy(str[i],p);
            i++;
            for(j=i-2;j>=0;j--)
            {
                if(strcmp(str[j],str[i-1])==0)
                    num[j]++;
            }
        }
        int max=0;
        for(j=1;j<i;j++)
        {
            if(num[j]<num[max])
                continue;
            if(num[j]>num[max])
            {
                max=j;
            }
            else
            {
                if(strcmp(str[max],str[j])>0)
                    max=j;
            }
        }
        printf("%s\n",str[max]);
    }
    return 0;
}
				

