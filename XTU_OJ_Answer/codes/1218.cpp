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
        for(int i=2;i*i<=sum;i++)//�ҳ�sum����������Ӧ����,sum��ֵһֱ�ڱ仯
        {
            if(sum%i==0)
            {
                int count=0;
                while(sum%i==0)
                {
                    count++;
                    sum=sum/i;
                }
                result*=(count+1);//�ڵó���ֱ�Ӽ���
                if(sum==1) break;
            }
        }
        if(sum!=1) result*=2;//�������һ�������Ļ������ӳ���2
        printf("%d\n",result);
    }
    return 0;
}
				

