// Problem: 1237
// Solution: 1956850
// Language: G++
// Result: Accepted
// Time: 686MS
// Memory: 22804KB





						
#include <stdio.h>
int bb[5000001]={0};
int b[1000000]= {0};
int main()
{
    int i,j,x,y,judge=1,a[500000];
    a[0] = 2;
    a[1] = 3;
    i = 2;
    y = 5;
    for(; a[i-1]<5000000; y++)//��������
    {
        judge = 1;
        for(x=0; a[x]*a[x]<=y; x++)//���y�ܱ�С�ڻ����y��ƽ����������������judge=0����˼Ϊ����Ϊ�٣�
        {
            if(y%a[x]==0){
                judge = 0;
            break;}
        }
        if(judge==1)//���y��������y��������a
        {
            a[i] = y;
            i++;
        }
    }
  //  printf("i:%d\n",i);
    for(i=1;i<=348514;i++){
       //     printf("%d\n",a[i]);
        if(a[i]==a[i-1]+2){
            j = a[i];
            bb[j] = 1;
   //         printf("bb[%d]:%d",j,bb[j]);
        }
    }
    for(i=6;i<=5000000;i++){
        bb[i] = bb[i-1]+bb[i];
 //   printf("bb%d\n",bb[i]);
    }
    int k,a1,a2;
    scanf("%d",&k);
    while(k--){
        scanf("%d %d",&a1,&a2);
        printf("%d\n",bb[a2]-bb[a1+1]);
    }
}
				

