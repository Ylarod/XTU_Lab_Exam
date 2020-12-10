// Problem: 1105
// Solution: 1959519
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1248KB





						
#include <stdio.h>
int gcd(int a,int b)
{
    if(a<0) a = 0-a;
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
        int a,b,c,d,fm,fz1,fz2,i,n,sum,cha;
        scanf("%d %d %d %d",&a,&b,&c,&d);
        fm = b*d;
        fz1 = a*d;
        fz2 = c*b;
        sum = fz1+fz2;
      //  printf("sum:%d cha:%d\n",sum,cha);
        cha = fz1-fz2;
        if(sum==0)printf("0 ");
        else if(sum%fm==0) printf("%d ",sum/fm);
        else printf("%d/%d ",sum/gcd(sum,fm),fm/gcd(sum,fm));
         if(cha==0)printf("0\n");
        else if(cha%fm==0) printf("%d\n",cha/fm);
        else printf("%d/%d\n",cha/gcd(cha,fm),fm/gcd(cha,fm));
    }
    return 0;
}

				

