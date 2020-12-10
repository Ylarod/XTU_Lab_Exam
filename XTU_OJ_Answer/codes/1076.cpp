// Problem: 1076
// Solution: 1881598
// Language: G++
// Result: Accepted
// Time: 437MS
// Memory: 1176KB





						
#include<stdio.h>
#include<math.h>
int main()
{
    while (1)
    {
        double n;
        scanf("%lf", &n);
         if (n == 1)
        {
            printf("No\n");
        }
        else if (n == 2)
        {
            printf("Yes\n");
        }
        else if (n == 3)
        {
            printf("Yes\n");
        }
        double d = 0,e;
        e = sqrt(n);
        for (int i = 2; i <= e; i++)
        {
            double b;

            b = n / i;

            d = b - (int)b;
            if (d == 0)
            {
                printf("No\n");
                break;
            }


        }
        if (d != 0)
        {
            printf("Yes\n");

        }if (n == 0)
        {
            break;
        }

    }

    return 0;
}

				

