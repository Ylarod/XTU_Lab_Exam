// Problem: 1109
// Solution: 1943189
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1124KB





						
#include <stdio.h>
int main ()
{
    int k,ca=1;
    char a[21][201]={0},b[202];
    scanf("%d",&k);
    while(k--)
    {
        int n,i=1,count=0;
        scanf("%d",&n);
        while(n--)
        {
            scanf("%s",&a[i]);
            count++;
            i++;
        }
        int judge=1,j;
        for(j=0; judge!=0; j++)
        {
            for(i=1; i<count; i++)
            {
                if(a[i][j]!=a[i+1][j]||a[i][j]=='\0')
                {
                    judge = 0;
                    break;
                }
            }
            b[j] = a[1][j];
        }
        b[j-1] = '\0';
        printf("Case %d: %s\n",ca,b);
        ca++;
    }
    return 0;
}

				

