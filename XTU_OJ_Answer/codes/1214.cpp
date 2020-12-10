// Problem: 1214
// Solution: 1958143
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1248KB





						

#include <stdio.h>  
#include <math.h>  
int main()  
{  
    int k; 
    int a,b,c,s,t; 
    scanf("%d",&k);  
    while(k--){  
        s=0,t=1;  
        scanf("%d+%d=%d",&a,&b,&c);  
        if(a+b==c){  
            printf("0\n");  
        }else{  
            for(int n=10;n<=1000000000;n*=10){  
                s++;  
                if(a*n+b==c){  
                    t=0;  
                    printf("%d\n",s);  
                }else continue;  
            }  
            if(t){  
                s=0;  
                for(int n=10;n<1000000000;n*=10){  
                    s--;  
                    if(a+b*n==c){  
                        printf("%d\n",s);  
                    }else continue;  
                }  
            }  
        }  
    }  
} 
				

