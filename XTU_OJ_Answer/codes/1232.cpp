// Problem: 1232
// Solution: 1956307
// Language: G++
// Result: Accepted
// Time: 31MS
// Memory: 1252KB





						
#include <stdio.h>
int yuefen(int a,int b){
    int c;
    while(b){
        a = a%b;
        c = b;
        b = a;
        a = c;
        }
        return a;
}
int main()
{
    int k;
    scanf("%d",&k);
    while(k--){
        int m,n,a,b,c,d,e;
        scanf("%d %d",&m,&n);
        if(m==0||n==0){
            printf("0\n");
        }else{
            a = m*n*2;
            b = (m+n)*(m+n-1);
            c = a/yuefen(a,b);
            d = b/yuefen(a,b);
            if(c!=d)printf("%d/%d\n",c,d);
            else printf("1\n");
        }
    }
    return 0;
}

				

