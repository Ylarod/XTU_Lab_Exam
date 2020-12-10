// Problem: 1251
// Solution: 2001831
// Language: G++
// Result: Accepted
// Time: 46MS
// Memory: 1140KB





						
#include <stdio.h>
int main()
{
    int t;
    int flag = 1;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        if(n<100)
        {
            int i,
                result = 0,
                cube;
            for(i=0;i<91;i++)
            {
                cube = i;
                while(cube)
                {
                    result += cube%10;
                    cube /= 10;
                }
                result += i;
                if(result==n)
                    flag = 0;
                result = 0;
            }
        }else{
            int i,
                result=0,
                cube;
            for(i=0;i<82;i++)
            {
                cube = n-i;
                while(cube)
                {
                    result += cube%10;
                    cube /= 10;
                }
                result += n-i;
                if(result==n)
                    flag = 0;
                result = 0;
            }
        }
        if(flag)
            printf("Yes\n");
        else
            printf("No\n");
        flag = 1;
    }
    return 0;
}

				

