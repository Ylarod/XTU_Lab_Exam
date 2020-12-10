// Problem: 1290
// Solution: 1978117
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1256KB





						
#include <stdio.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--)
    {
        char a[15],b[15];
        scanf("%s %s",a,b);
        getchar();
        int judge;
        judge = a[0]-b[0];
        if(judge==0)
            printf("Draw\n");
        else if(judge==-1||judge==3||judge==-2)
            printf("Alice\n");
        else
            printf("Bob\n");
    }
    return 0;
}

				

