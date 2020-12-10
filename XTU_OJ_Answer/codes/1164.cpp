// Problem: 1164
// Solution: 1964405
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1252KB





						
#include <stdio.h>
#include <string.h>
int main()
{
    char a[102];
    int lena,i,j,sum;
    while(scanf("%s",a)!=EOF)
    {
        getchar();
        lena = strlen(a);
        sum = 0;
        for(i=0;i<lena;i++)
        {
            if(a[i]=='0') sum++;
            else if(a[i]=='4') sum++;
            else if(a[i]=='6') sum++;
            else if(a[i]=='8') sum += 2;
            else if(a[i]=='9') sum++;
        }
        printf("%d\n",sum);
    }
    return 0;
}
				

