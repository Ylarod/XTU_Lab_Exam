// Problem: 1279
// Solution: 1933001
// Language: G++
// Result: Accepted
// Time: 187MS
// Memory: 6996KB





						
#include <stdio.h>
int b[1000001]= {0};
int main()
{
    int i,j,x,y=5,judge=1,a[500000]= {2,3},ab,bb,k;
    for(i = 2; a[i-1]<1000000; y++)//����һ�������� ��������a�� ���ɸѡ����Ч�ʲ��� ���鿴����ɸ
    {
        judge = 1;
        for(x=0; a[x]*a[x]<=y; x++)
        {
            if(y%a[x]==0)
            {
                judge = 0;
                break;
            }
        }
        if(judge==1)
        {
            a[i] = y;
            i++;
        }
    }
    for(i=0; a[i]<=1000; i++)//��˫�����ı� ��������b�� []��ĵ�����˫�����͸�����ֵΪһ
    {
        for(j=i; a[j]<500000; j++)
        {
            if(i!=j&&a[i]*a[j]<1000000)
                b[a[i]*a[j]] = 1;
        }
    }
    for(i=3; i<1000001; i++)//�ӵ���������Ϊǰ��������0û��Ҫ������ʼÿ��������������ǰһ����
    {
        b[i] += b[i-1];
    }//ѭ������������ֵ����1��[]�������˫�����ĸ���
    scanf("%d",&k);
    while(k--)
    {
        scanf("%d %d",&ab,&bb);
        printf("%d\n",b[bb]-b[ab-1]);
    }
    return 0;
}
//ps�������ð�ɸһ�δ�����ܰ�˫������Ƴ���

				
