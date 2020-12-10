// Problem: 1292
// Solution: 1956931
// Language: G++
// Result: Accepted
// Time: 31MS
// Memory: 1248KB





						
 #include <stdio.h>
 #include <string.h>
 int main()
 {
     int k,lena,n,i,j,n0,z;
     scanf("%d",&k);
     while(k--){
        char a[1002],judge=1;
        scanf("%s",&a);
        lena = strlen(a);
        for(n=lena/2;n;n--){//printf("\nn:%-3d",n);
            for(j=0;j<=lena-n*2;j++){judge =1;//printf("j:%-3d",j);
                for(i=0;i<n;i++){
                    if(a[j+i]!=a[j+n+i]){
                        judge = 0;
                      //  printf("²âÊÔ1");
                        break;
                       // printf("²âÊÔ2\n");
                    }
                  //  printf("i:%-2djudge:%-2d\n",i,judge);
                }if(judge==1) break;
            }if(judge==1) break;
        }
        if(n==1&&judge==0) printf("0\n");
        else printf("%d\n",2*n);
     }
     return 0;
 }

				

