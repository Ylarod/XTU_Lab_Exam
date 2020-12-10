// Problem: 1097
// Solution: 1978561
// Language: G++
// Result: Accepted
// Time: 31MS
// Memory: 1256KB





						
#include <stdio.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--)
    {
        int n,i,j,a[1002];
        char ch;
        scanf("%d %c",&n,&ch);
        for(i=0;i<n;i++)
            scanf("%d",&a[i]);
        int flag=1;
        while(flag)
        {
            flag = 0;
            for(i=0;i<n-1;i++)
            {
                if(a[i]>a[i+1])
                {
                    j = a[i];
                    a[i] = a[i+1];
                    a[i+1] = j;
                    flag = 1;
                }
            }
        }
        for(i=0;i<n;i++)
        {
            if(ch=='A')
                j =i;
            else
                j = n-i-1;
            printf("%d",a[j]);
            if(i<n-1)
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}

				

