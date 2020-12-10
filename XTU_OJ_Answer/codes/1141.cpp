// Problem: 1141
// Solution: 1959374
// Language: G++
// Result: Accepted
// Time: 78MS
// Memory: 1256KB





						
#include <stdio.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--){
        char a[30]={0};
        int i,x,y,z,n,sum,yu,judge;
        scanf("%d",&n);
        i = 0;
        while(n){
            yu = n%3;
            n /= 3;
           // printf("yu:%d\n",yu);
            if(yu==1) a[i] += 1;
            if(yu==0) a[i] += 0;
            if(yu==2) a[i] += 2;
          //  printf("a[%d]:%d\n",i,a[i]);
            if(a[i]<2){
                judge = 0;
                if(a[i]==1) a[i] = '1';
                if(a[i]==0) a[i] = '0';
            }else{
            if(a[i]==2){
                a[i] = '-';
                a[i+1] = 1;
            }
            if(a[i]==3){
                a[i] = '0';
                a[i+1] = 1;
            }
            judge = 1;
            }
          //  printf("×Ö·ûa[%d]:%c\n",i,a[i]);
            i++;
        }
     //   printf("judge:%d\n",judge);
        if(judge==0) i--;
        else a[i] +=48;
        for(;i>=0;i--) printf("%c",a[i]);
        printf("\n");
    }
}

				

