// Problem: 1130
// Solution: 1915693
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1168KB





						
#include <stdio.h>
int main()
{
    int k,i;
    scanf("%d",&k);
    while(k--){
        char a[100]={0},b[20001];
        scanf("%s",&b);
        for(i=0;b[i]!='\0';i++){
           a[b[i]] ++;
        }
        int ch=65;
        for(i=66;i<=90;i++){
            if(a[65]<a[i]){
                a[65]=a[i];
                ch=i;
            }
        }
        printf("%c %d\n",ch,a[65]);
    }
    return 0;
}

				

