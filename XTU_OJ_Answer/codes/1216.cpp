// Problem: 1216
// Solution: 1958756
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1252KB





						
#include <stdio.h>
#include <string.h>
int zhuanhuan(int a)
{
    if(a=='I')
        a = 1;
    else if(a=='V')
        a = 5;
    else if(a=='X')
        a = 10;
    else if(a=='L')
        a = 50;
    else if(a=='C')
        a = 100;
    else if(a=='D')
        a = 500;
    else if(a=='M')
        a = 1000;
    return a;
}
int shijinzhi(int a,int b)
{
    a = zhuanhuan(a);
    b = zhuanhuan(b);
    if(a<b)
        return a-b;
    else
        return a;
}
int main()
{
    int k,lena;
    char a[27];
    while(scanf("%s",&a)!=EOF){
        int sum=0,i=0,n,z;

        lena = strlen(a)-1;
        if(lena==0){
            printf("%d\n",zhuanhuan(a[0]));
        }else{
        while(i<lena){
            n = shijinzhi(a[i],a[i+1]);
            if(n>0) sum += n;
            else{
                sum -= n;
                i++;
            }
            i++;
        }
        if(zhuanhuan(a[lena])<=zhuanhuan(a[lena-1]))
            sum += zhuanhuan(a[lena]);
            printf("%d\n",sum);
    }
    }
}

				

