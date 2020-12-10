// Problem: 1116
// Solution: 1885928
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1160KB





						
#include <stdio.h>
int main()
{/*蛐蛐大神保平安*/
    int n,yu,he,i,cifang,k,count=0;
    scanf("%d",&n);
    while(n){

    i=n;
    he=0;
    count=0;
    while(i){
        i=i/10;
        count++;
    }
    i=n;
        while(i){
            yu=i%10;
            i=i/10;
            k=count;
            cifang=1;
            while(k--){
                cifang=cifang*yu;
            }
            he=he+cifang;
        }
        he=he-n;
        if(he==0)
            printf("Yes\n");
        else
        printf("No\n");
                    scanf("%d",&n);
        }
}

				

