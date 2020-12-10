// Problem: 1233
// Solution: 1956222
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1252KB





						
#include <stdio.h>
int main()
{
    int k,zz;
    scanf("%d",&k);
    zz = k;
    while(zz){
       // printf("k:%d\n",zz);
        int i,j,a,b,n,n0,n1;
        char ch,biao[57][57];
        scanf("%d",&ch);
        n= ch*2-1;
        ch = ch+'A'-1;
        n0 = 0;
        n1 = n;
        while(n0<n1){
        for(i=n0;i<n1;i++){
            for(j=n0;j<n1;j++){
                biao[i][j] = ch;
            }
        }
        ch--;
        n0++;
        n1--;
        }
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
             printf("%c",biao[i][j]);
            }
            printf("\n");
        }
       // printf("²âÊÔ1\n");
       zz--;
    //   printf("kÄ©Î²%d\n",zz);
    }
 //   printf("²âÊÔ2");
    return 0;
}

				

