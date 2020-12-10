// Problem: 1114
// Solution: 1942751
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1128KB





						
#include <stdio.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--){
        char a[202],b[202];
        int x,y,i,z;
        scanf("%s",&a);
        scanf("%d %d",&x,&y);
        z=x+y-2;
        for(i=x-1;i<=x+y-2;i++){
            b[i] = a[z];
            z--;
        }
        for(i=x-1;i<=x+y-2;i++){
            a[i] = b[i];
        }
        printf("%s\n",a);
    }
    return 0;
}

				

