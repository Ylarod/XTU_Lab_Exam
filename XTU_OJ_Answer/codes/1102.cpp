// Problem: 1102
// Solution: 1886184
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1160KB





						
#include <stdio.h>
int main()
{/*蛐蛐大神保平安*/
    int x,y,n,judge,a,b;
    scanf("%d",&n);
    while(scanf("%d %d",&x,&y)&&n--){
    int count=0;
        if(x<y)
        {
            judge=x;
            x=y;
            y=judge;
        }
        while(x){
            a=x%2;
            b=y%2;
            x=x/2;
            y=y/2;
          //  printf("a%d_b%d\n",a,b);
            judge=a-b;
            if(judge!=0)
            count++;
           //  printf("%d\n",count);
        }
        printf("%d\n",count);
    }
    return 0;
}

				

