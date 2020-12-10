// Problem: 1266
// Solution: 1964672
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1260KB





						
#include <stdio.h>
#include <string.h>
int main()
{
    char z[10002];
    while(scanf("%s",z)!=EOF)
    {
        getchar();
        int lena,sum=0,x=0,y=0,zz,a=0,b=0,c=0,d=0,i,flag=0;
        lena = strlen(z);
        for(i=0;i<lena;i++)
        {
            if(z[i]=='R') x++;
            else if(z[i]=='G') y++;
            else if(z[i]=='B') zz++;
        }
        for(i=0;i<x;i++)
        {
            if(z[i]=='G') a++;
            else if(z[i]=='B') b++;
        }
      //  printf("%d %d\n",a,b);
        for(i=x;i<y+x;i++)
        {
            if(z[i]=='R') c++;
            else if(z[i]=='B') d++;
        }
      //  printf("%d %d\n",c,d);
        if(c>a){
            flag = 1;
        }else{
            flag = 0;
        }
        sum = a+b+d+flag*(c-a);
        printf("%d\n",sum);
    }
    return 0;
}

				

