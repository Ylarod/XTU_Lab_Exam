// Problem: 1290
// Solution: 1885375
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1160KB





						
#include<stdio.h>
int main()
{
    int k,judge;
    char a[10],b[10];
    scanf("%d",&k);
    while(k--){
        scanf("%s",a);
        getchar();
        scanf("%s",b);
        judge=a[0]-b[0];
        if(judge==0){
            printf("Draw\n");
        }else{
            if(judge==1||judge==2||judge==(0-3)){
                printf("Bob\n");
            }else{
                printf("Alice\n");
            }
        }
    }
return 0;
}
				

