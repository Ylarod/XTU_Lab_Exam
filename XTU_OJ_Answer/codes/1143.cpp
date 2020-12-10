// Problem: 1143
// Solution: 1958984
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1256KB





						
#include <stdio.h>
#include <string.h>
int main(){
    char a[201];
    char b[201];
    int n,k,i,j,tag;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%s",&a);
        getchar();
        scanf("%s",&b);
        getchar();
        //puts(a);
       // printf("A:%s\n",a);
        //printf("B:%s\n",b);
        tag=0;
        for(i=0,j=0;i<strlen(a);i++)
        {
           // j=0;
           //// printf("a[%d]:%d b[%d]:%d\n",i,a[i],j,b[j]);
            if(a[i]==b[j]) j++;
            if(j==strlen(b))
            {
                tag=1;
                break;
            }
        }
        if(tag==1) puts("Yes");
        else puts("No");
    }
    return 0;
}

				

