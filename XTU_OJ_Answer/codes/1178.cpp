// Problem: 1178
// Solution: 1943588
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1124KB





						
#include <stdio.h>
int paio(int a,int b){
    int z;
if(a>b){
            z = a;
            a = b;
            b = z;
        }
        return a;
}
int pait(int a,int b){
    int z;
if(a>b){
            z = a;
            a = b;
            b = z;
        }
        return b;
}
int judge(int a,int b,int c,int d){
if(a<d&&b>c) return 1;
else return 0;
}
int main()
{
    int k;
    scanf("%d",&k);
    while(k--){
        int a,b,c,d,x1,y1,x2,y2,pd1,pd2,z;
        scanf("%d %d %d %d",&a,&b,&c,&d);
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
        z = a;
        a = paio(a,c);
        c = pait(z,c);
        z = b;
        b = paio(b,d);
        d = pait(z,d);
        z = x1;
        x1 = paio(x1,x2);
        x2 = pait(z,x2);
        z = y1;
        y1 = paio(y1,y2);
        y2 = pait(z,y2);
        pd1 = judge(a,c,x1,x2);
        pd2 = judge(b,d,y1,y2);
    if(pd1&&pd2) printf("Yes\n");
    else printf("No\n");
    }
    return 0;
}

				

