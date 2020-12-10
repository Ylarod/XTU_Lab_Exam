// Problem: 1189
// Solution: 1901789
// Language: G++
// Result: Accepted
// Time: 62MS
// Memory: 1164KB





						
#include<stdio.h>

#include<math.h>

int main()

{

    int n;

    int a,b,c,s;

    scanf("%d",&n);

    while(n--)

    {

        scanf("%d %d %d",&a,&b,&c);

        if(c == 1)

        {

            if(a==b&&b!=0)

                printf("0\n");

            else if(a==b&&b==0)

                printf("1\n");

            else if(a!=b)

                printf("None\n");

        }

        else if(c == 0)

        {

            if(a==0&&b!=0) printf("0\n");
            if(a==0&&b==0) printf("None\n");

            else if(a>0)  printf("None\n");



        }

        else if(c>1)

        {

            if (b*c>a)  printf("None\n");

            else if(a==b)

                printf("None\n");



            else
            {

                s=(b*c-a)%(1-c);

                if(s==0){
                    s=(b*c-a)/(1-c);
                    printf("%d\n",s);
                }
                else printf("None\n");
            }

        }

    }

    return 0;

}

				

