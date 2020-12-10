// Problem: 1235
// Solution: 1956366
// Language: G++
// Result: Accepted
// Time: 30MS
// Memory: 1256KB





						
#include <stdio.h>
#include <string.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--){
        char a[202],b[202],lena,lenb,i;
        scanf("%s %s",&a,&b);
        lena = strlen(a);
        lenb = strlen(b);
        for(i=0;i<lena-1;i++){
            printf("%c",a[i]);
            printf("%c",b[lenb-i-1]);
        }
        printf("%c\n",a[lena-1]);
    }
    return 0;
}

				

