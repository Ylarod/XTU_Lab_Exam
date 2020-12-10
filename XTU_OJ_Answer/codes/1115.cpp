// Problem: 1115
// Solution: 1943586
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1128KB





						
#include <stdio.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--){
        char a[202];
        int x,y,i,n,z,judge=1;
        scanf("%s",&a);
        scanf("%d %d",&x,&y);
        z = x+y-2;
        for(i=x-1;i<=z;+i++){
            if(a[i]!=a[z]){
                judge = 0;
                break;
            }
            z--;
                    }
       if(judge==1) printf("Yes\n");
       else printf("No\n");
    }
    return 0;
}

				

