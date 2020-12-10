// Problem: 1137
// Solution: 1959229
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1252KB





						
#include <stdio.h>
int main()
{
    int k;
    scanf("%d",&k);
    getchar();
    while(k--){
           // printf("k:%d\n",k);
        char ch;
        int i,a,b,n;
        scanf("%c",&ch);
        getchar();
        n = ch-64;
        for(i=65,a=1;a<=n;a++){
            for(b=0;b<n;b++)printf(" ");
            printf("%c\n",i);
            for(b=0;b<n-a;b++)printf(" ");
            for(b=0;b<2*a+1;b++)printf("%c",i);
            printf("\n");
            i++;
        }
    }
}

				

