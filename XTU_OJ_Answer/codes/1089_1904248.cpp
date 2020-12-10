// Problem: 1089
// Solution: 1904248
// Language: G++
// Result: Accepted
// Time: 109MS
// Memory: 1164KB





						
#include <stdio.h>
int main()
{
    int k,n,a,i;
    while(k=scanf("%d",&n)==1){
            int judge=0,judgetwo=0,count=0;
    for(i=2;i*i<=n;){
    if((n%i)==0){
     count++;
     n=n/i;
     }
     else{
        if(count>1)
        printf("%d^%d*",i,count);
        else if(count==1)
        printf("%d*",i);
        i++;
        count=0;
    }
    }
    if(i<=n){
            if(count==0)printf("%d\n",n);
       else {if(n==i)printf("%d^%d\n",i,count+1);
       if(n>i){if(count==1)printf("%d*%d\n",i,n);
       if(count>1)printf("%d^%d*%d\n",i,count,n);}
    }
    }
    }
    return 0;
}

				

