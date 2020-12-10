// Problem: 1187
// Solution: 1964610
// Language: G++
// Result: Accepted
// Time: 46MS
// Memory: 1256KB





						
#include <stdio.h>
int mo=1000000007;
__int64 x,y,z;
int main()
{//printf("≤‚ ‘1\n");
    int n,i,j;
    while(scanf("%d",&n)&&n!=0)
    {
        int sum=0;
        x = n/3;
        y = n/3;
        z = n/3;
        if(n%3==2)
        {
            y++;
            z++;
        }else if(n%3==1){
            y++;
        }
        sum = ((x*(x-1)*(x-2)/6)%mo+(y*(y-1)*(y-2)/6)%mo+(z*(z-1)*(z-2)/6)%mo+x*y*z%mo)%mo;
    printf("%d\n",sum);
    }
    return 0;
}

				

