// Problem: 1273
// Solution: 1965053
// Language: G++
// Result: Accepted
// Time: 1436MS
// Memory: 1636KB





						
#include <stdio.h>
int a[100002];
int jdz(int a, int b)
{
    if(a-b>0)
        return a-b;
    else
        return b-a;
}
int main ()
{
    int k,i,j,judge,b[7];
    scanf("%d",&k);
    while(k--)
    {
        int n,sum=0;
        scanf("%d",&n);
        j = n;
        while(n--)
        {
            scanf("%d",&a[n]);
          //  printf("%d\n",n);
            if(sum<5)
            {
                 sum++;
                for(i=n;i<j;i++)
                {
                    if(a[i]==a[n]&&n!=i)
                    {
                        sum--;
                        break;
                    }else{
                        b[sum] = a[n];
                    }
                }
            }
        }
       // printf("sum:%d\n",sum);
      //  printf("b1:%d %d %d %d",b[1],b[2],b[3],b[4]);
        if(sum>4) printf("No\n");
        else if(sum==4){
            for(i=2;i<4;i++)
            {
                if(b[1]>b[i])
                {
                    j = b[1];
                    b[1] = b[i];
                    b[i] = j;
                }
                if(b[4]>b[i])
                {
                    j = b[4];
                    b[4] = b[i];
                    b[i] = j;
                }
            }
           // printf("b2:%d %d %d %d\n",b[1],b[2],b[3],b[4]);
            if(jdz(b[1],b[4])==jdz(b[2],b[3]))
                printf("Yes\n");
            else
                printf("No\n");
        }else if(sum<4) printf("Yes\n");
    }
    return 0;
}

				

