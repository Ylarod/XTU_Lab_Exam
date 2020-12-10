// Problem: 1149
// Solution: 1960745
// Language: G++
// Result: Accepted
// Time: 93MS
// Memory: 1328KB





						
#include <stdio.h>
int main()
{
    int a,b,c;
    while(scanf("%d %d %d",&a,&b,&c)!=EOF){
        int i,x,y,z,sum,judge=1;
        int m[10001]={0};
        int n[10001]={0};
        for(i=1;i<=c;i++){
            n[i] = (a*n[i-1]+b)%c;
        }
         for(i=1;i<=c;i++){
           m[n[i]] = 1;
           //printf("m[%d]:%d\n",n[i],m[n[i]]);
        }
         for(i=1;i<c;i++){
            if(m[i]==0) judge = 0;
        }
        if(judge) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
/*����ͬ��������������ǰ�Xn+1 = (aXn+c)%m �����ģ�����X0=0�� ����ϣ���ܲ������е�0~m-1���������ڸ���һϵ�е�a,c,m,�����һ���Ƿ��ܲ������е�0~m-1������

����
�ж���������ÿ������һ�У�Ϊ����������a(1��a;��10,000),c(0��c��100,000),m(1��m��10,000)��

���
ÿ�����һ�������Ľ��������ܲ�������0~m-1���������Yes���������No��

��������
1 2 7
2 3 5

�������
Yes
No*/

				

