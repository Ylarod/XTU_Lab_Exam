// Problem: 1277
// Solution: 1935262
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1128KB





						
#include <stdio.h>
int main()
{
    int k;
char ch;
    while(scanf("%c",&ch)!=EOF){
        char ch2;
        int hs,count,judge,a,b,x,y,c,z,kgy,i;
        getchar();
        kgy = ch-64;
             a = kgy+kgy-1;
        for(hs=1;hs<=kgy;hs++){
           // printf("%d",kgy);
       //                         printf("����%d",hs);
        b = a;
            for(i=0;i<b;i++){

                printf(" ");
            }//���ƿո�
            judge = 64+hs;
            for(ch2=65;ch2<judge;ch2++){
                printf("%c",ch2);
            }//������ĸ
            for(;ch2>=65;ch2--){
                printf("%c",ch2);
            }//������ĸ
            printf("\n");
            a--;
        }//��һ��������
        a = kgy-1;
          x = kgy+kgy-1;
        for(hs=1;hs<=kgy;hs++){
                b = a;
            for(i=0;i<b;b--){
                printf(" ");
            }//���Ƶ�һ�οո�
             judge = 64+hs;
            for(ch2=65;ch2<judge;ch2++){
                printf("%c",ch2);
            }//������ĸ
            for(;ch2>=65;ch2--){
                printf("%c",ch2);
            }//������ĸ

              b = x;
            for(i=0;i<b;b--){

                printf(" ");

            }//���Ƶڶ��οո�
             a--;
             x--;
             x--;
          judge = 64+hs;
            for(ch2=65;ch2<judge;ch2++){
                printf("%c",ch2);
            }//������ĸ
            for(;ch2>=65;ch2--){
                printf("%c",ch2);
            }//������ĸ
            printf("\n");
        }//��������������  */
    }
    return 0;
}
				

