// Problem: 1140
// Solution: 1959350
// Language: G++
// Result: Accepted
// Time: 31MS
// Memory: 1252KB





						
#include <stdio.h>
#include <string.h>
int zhuanhuan(char a[])
{
    int sum=0,lena,i;
    lena = strlen(a);
    for(i=0;i<lena;i++){
        if(a[i]=='-') a[i] = 0-1;
        else a[i] -= 48;
        sum = sum*3+a[i];
    }
    return sum;
}
int main()
{
    int k,sum;
    scanf("%d",&k);
    while(k--){
        char str[30];
        scanf("%s",&str);
        printf("%d\n",zhuanhuan(str));
    }
}

				

