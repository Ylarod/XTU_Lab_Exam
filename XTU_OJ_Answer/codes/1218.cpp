// Problem: 1218
// Solution: 1960434
// Language: G++
// Result: Accepted
// Time: 311MS
// Memory: 2240KB





						

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAX 1000
int A[MAX];
int main()
{
    int a,b,sum;
    int K;
    scanf("%d",&K);
    while(K--)
    {
        int result=1;
        scanf("%d%d",&a,&b);
        sum=a+b;
        for(int i=2;i*i<=sum;i++)//找出sum的因子所对应的幂,sum的值一直在变化
        {
            if(sum%i==0)
            {
                int count=0;
                while(sum%i==0)
                {
                    count++;
                    sum=sum/i;
                }
                result*=(count+1);//在得出后直接计算
                if(sum==1) break;
            }
        }
        if(sum!=1) result*=2;//最后还留下一个质数的话，还加乘以2
        printf("%d\n",result);
    }
    return 0;
}
				

