// Problem: 1138
// Solution: 1959244
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1248KB





						
#include <stdio.h>
int gcd(int a,int b)
{
    int c;
    while(b){
        a = a%b;
        c = a;
        a = b;
        b = c;
    }
    return a;
}
int main()
{
    int k;
    scanf("%d",&k);
    while(k--){
        int a,b,c,d,i,n,sum,z;
        scanf("%d %d",&a,&b);
        if(b==0||b==1)printf("1\n");
        else if(a==b) printf("0\n");
        else{
            c = a*a-a;
            d = b*b-b;
            d = c-d;
            printf("%d/%d\n",d/gcd(c,d),c/gcd(c,d));
        }
    }
}

				

