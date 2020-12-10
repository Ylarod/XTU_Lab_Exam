// Problem: 1234
// Solution: 1961287
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1252KB





						
#include <stdio.h>
#include <string.h>
int pd(char a)
{
    int b,c,d;
    if((a>=48&&a<=57)||(a>=65&&a<=90)||(a>=97&&a<=122)||a==95)
        return 1;
    else
        return 0;
}
int main()
{
    int k;
    char z[33][40]={"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","typedef","union","unsigned","void","volatile","switch","struct","while"};
    scanf("%d",&k);
    while(k--){
            int i,judge=1,lena;
        char a[40];
        scanf("%s",a);
        lena = strlen(a);
    for(i=0;i<32;i++){
        judge = strcmp(a,z[i]);
        if(judge==0)
        break;
    }
    if(judge!=0){
        if(a[0]>=48&&a[0]<=57){
            judge = 0;
        }else{
            for(i=0;i<lena;i++){
                if(pd(a[i])==0){
                    judge = 0;
                    break;
                }
            }
        }
    }
    if(judge)
        printf("Yes\n");
    else
        printf("No\n");
    }
    return 0;
}
/*auto break case char const continue default do double else enum extern
float for goto if int long register return short signed sizeof static
struct switch typedef union unsigned void volatile while*/

				

