// Problem: 1035
// Solution: 1980214
// Language: G++
// Result: Accepted
// Time: 30MS
// Memory: 1264KB





						
#include <stdio.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--)
    {
        int n;
        scanf("%d",&n);
        int a[1002];
        int i;
        for(i=0; i<n; i++)
        {
            scanf("%d",&a[i]);
        }
        int b[1002],c[1002];
        for(i=0; i<n; i++)
        {
            c[i] = i+1;
        }
        b[0] = 1;
        i = 0;
        int j=0,k=0,flag=1;
        while(i<n-1)
        {
            if(b[j]!=a[i])
            {
                k++;
                j++;
                if(k>n)
                {
                    flag = 0;
                    break;
                }
                b[j] = c[k];
            }
            else
            {
                i++;
                j--;
            }
        }
        if(flag)
            printf("Yes\n");
        else
            printf("No\n");
    }
}

				

