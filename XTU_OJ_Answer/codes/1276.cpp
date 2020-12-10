// Problem: 1276
// Solution: 1933254
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1140KB





						
#include <stdio.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--){
        int x,y,judge=0;
        double pj;
        scanf("%d %d",&x,&y);
        pj = x+y;
      //  printf("%lf\n",pj-x);
         pj = pj/2;
        if(x>pj)
        printf("Bob %g\n",pj-y);
        else if(x<pj)
        printf("Alice %g\n",pj-x);
        else
        printf("None\n");
    }
    return 0;
}

				

