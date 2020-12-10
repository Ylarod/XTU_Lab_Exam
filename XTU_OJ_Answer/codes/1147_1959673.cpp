// Problem: 1147
// Solution: 1959673
// Language: G++
// Result: Accepted
// Time: 61MS
// Memory: 1252KB





						
#include <stdio.h>
#include <string.h>
int main()
{
    int k;
    scanf("%d",&k);
    getchar();
    while(k--){
        char a[1002],b[3];
        gets(a);
      //  puts(a);
        gets(b);
         int i,lena;
    lena = strlen(a);
    for(i=0;i<lena;i++){
        if(a[i]==b[0])
            printf("\n");
        else
            printf("%c",a[i]);
    }
        printf("\n");
       // printf("²âÊÔ\n");
    }
}

				

