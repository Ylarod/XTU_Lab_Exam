// Problem: 1291
// Solution: 1955959
// Language: G++
// Result: Accepted
// Time: 109MS
// Memory: 1248KB





						
#include <stdio.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--)
    {
        int a[1002];
        int m,n,i,j,judge=1,min=0,cha=101,min2=0;
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++){
            scanf("%d",&a[i]);
        }
       // printf("≤‚ ‘0");
        while(judge){
                judge = 0;
             for(i=1;i<n;i++){
                if(a[i]>a[i-1]){
                j = a[i];
                a[i] = a[i-1];
                a[i-1] = j;
                judge = 1;
                }
            }
        }
      // printf("≤‚ ‘1\n");
        for(i=0;i<m;i++){
            min += a[i];
        }
     //   printf("≤‚ ‘2\n");
        int a1,a2;
        for(i=0;i+m-1<n;i++){
            j = a[i]-a[i+m-1];
            if(cha==j){
                for(a2=i,min2=0;a2<i+m;a2++){
                    min2 += a[a2];
                }
                if(min2<min) min = min2;
            }
      //      printf("≤‚ ‘3\n");
            if(cha>j){
                cha = j;
                for(a2=i,min=0;a2<i+m;a2++){
                    min += a[a2];
                }
            }
        }
      //  printf("≤‚ ‘4\n");
        printf("%d %d\n",cha,min);
    }
}



				

