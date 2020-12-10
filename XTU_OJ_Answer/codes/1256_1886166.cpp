// Problem: 1256
// Solution: 1886166
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1128KB





						
#include <stdio.h>
int main()
{/*蛐蛐大神保平安*/
    int k,countx,countt,countu,i;
    char a[1001];
    scanf("%d",&k);
    getchar();
    while(k--){
        gets(a);
        countx=0;
        countt=0;
        countu=0;
        for(i=0;a[i]!='\0';i++){
            if(a[i]==84)
            countt++;
            if(a[i]==85)
            countu++;
            if(a[i]==88)
            countx++;
        }
        if(countx>countt)
            countx=countt;
        if(countx>countu)
            countx=countu;
        printf("%d\n",countx);
    }
}
				

