// Problem: 1145
// Solution: 1959541
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1252KB





						
#include <stdio.h>
int main()
{
    int k;
    while(scanf("%d",&k)&&k!=0){
        int a[40]={0},b[40]={0},c,d,i,n,sum,flag=0,tag,judge=1,x,y,z;
        i = k;
        while(i--){
            scanf("%d",&a[i]);
          //  printf("a[%d]:%d",i,a[i]);
        }
        i = k;
        while(i--){
            scanf("%d",&b[i]);
          //  printf("b[%d]:%d",i,b[i]);
        }
        i = k;
        while(i--){
            if(a[i]>b[i]) flag = 1;
            if(a[i]<b[i]) judge = 0;
        }
        if(judge==1&&flag==1)
            printf("1\n");
        else if(flag==0&&judge==0)
            printf("-1\n");
        else printf("0\n");
    }
}

				

