// Problem: 1213
// Solution: 1957089
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1248KB





						
#include<stdio.h>
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
    int a,b,c,d;
    scanf("%d %d",&a,&b);
    if(b<3) printf("0\n");
    else{
            if(a==b) printf("1\n");
        else{
            c = b*(b-1)*(b-2);
            d = a*(a-1)*(a-2);
            printf("%d/%d\n",c/yuefen(c,d),d/yuefen(c,d));
        }
    }
    }
}

				

