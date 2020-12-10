// Problem: 1215
// Solution: 1958739
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1252KB





						
#include <stdio.h>
int quanzhong(int a){
    int result=1;
    while(a--)
    {
        result *=10;
    }
    return result;
}
int main()
{
    int k;
    scanf("%d",&k);
    while(k--){
        int a,b,c,d,i=0,n,sum=0;
        scanf("%d %d",&a,&b);
        while(a||b){
            c = a%10;
            d = b%10;
            n = (c+d)%10;
            sum += n*quanzhong(i);
            a /= 10;
            b /= 10;
            i++;
        }
        printf("%d\n",sum);
    }
    return 0;
}

				

