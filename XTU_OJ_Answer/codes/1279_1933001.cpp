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
    for(i = 2; a[i-1]<1000000; y++)//打了一个素数表 存在数组a里 这个筛选方法效率不高 建议看看埃筛
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
    for(i=0; a[i]<=1000; i++)//打双素数的表 存在数组b里 []里的的数是双素数就给他赋值为一
    {
        for(j=i; a[j]<500000; j++)
        {
            if(i!=j&&a[i]*a[j]<1000000)
                b[a[i]*a[j]] = 1;
        }
    }
    for(i=3; i<1000001; i++)//从第三个（因为前两个都是0没必要）数开始每个数渡倚自身加前一个数
    {
        b[i] += b[i-1];
    }//循环完后各个数得值就是1到[]里的数的双素数的个数
    scanf("%d",&k);
    while(k--)
    {
        scanf("%d %d",&ab,&bb);
        printf("%d\n",b[bb]-b[ab-1]);
    }
    return 0;
}
//ps：建议用埃筛一次打表就能把双素数标计出来

				

