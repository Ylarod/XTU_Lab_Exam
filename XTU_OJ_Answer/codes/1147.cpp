// Problem: 1147
// Solution: 1959667
// Language: G++
// Result: Accepted
// Time: 77MS
// Memory: 1252KB





						
#include <stdio.h>
#include <string.h>
int main()
{
    int k;
    scanf("%d",&k);
    getchar();
    while(k--){
        char a[1002],b;
        gets(a);
      //  puts(a);
        scanf("%c",&b);
        getchar();
         int i,lena;
    lena = strlen(a);
    for(i=0;i<lena;i++){
        if(a[i]==b)
            printf("\n");
        else
            printf("%c",a[i]);
    }
        printf("\n");
       // printf("²âÊÔ\n");
    }
}

				

