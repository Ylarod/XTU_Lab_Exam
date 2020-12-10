// Problem: 1223
// Solution: 1965482
// Language: G++
// Result: Accepted
// Time: 375MS
// Memory: 1248KB





						
#include<stdio.h>

int main()
{
    int k;
    scanf("%d",&k);
    while(k--)
    {
        int m;
        scanf("%d",&m);
        int sum=1,i=1,j=1,n;
        if(m==1) printf("1\n");
        else if(m%2==0||m%5==0) printf("0\n");
        else{
        j=i=j%m;
        do{
        j=j*10+1;
        j=j%m;
        sum++;
        }while(j!=i&&j>0);
        if(j==i) printf("0\n");
        else printf("%d\n",sum);
        }
    }
    return 0;
}










				

