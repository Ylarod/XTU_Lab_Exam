// Problem: 1146
// Solution: 1961217
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1256KB





						
#include <stdio.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--){
        int m,n,i,j,sum,judge,result,A1,A2,B1,B2;
        int a[11][11]={0},b[11][11]={0},c[11][11]={0};
        scanf("%d %d",&A1,&A2);
        for(i=0;i<A1;i++){
            for(j=0;j<A2;j++){
                scanf("%d",&a[i][j]);
            //    printf("a[%d][%d]:%-3d",i,j,a[i][j]);
            }
            //printf("\n");
        }
        scanf("%d %d",&B1,&B2);
        for(i=0;i<B1;i++){
            for(j=0;j<B2;j++){
                scanf("%d",&b[i][j]);
            //    printf("b[%d][%d]:%-3d",i,j,b[i][j]);
            }
           // printf("\n");
        }
        for(i=0;i<A1;i++){
            for(j=0;j<A2;j++){
                for(m=0;m<B2;m++){
                      //  printf("m:%d",m);
                     c[i][m] += a[i][j]*b[j][m];
                   //  printf("c[%d][%d]:%-3d = a[%d][%d]:%-3d*b[%d][%d]:%-3d",i,m,c[i][m],i,j,a[i][j],j,m,b[j][m]);
                }
               // printf("\n");
            }
        }
        for(i=0;i<A1;i++){
            for(j=0;j<B2;j++){
                if(j!=0) printf(" ");
                printf("%d",c[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}

/*����
��һ����һ������K����ʾ�����ĸ����� ÿ������������������A��B�� ÿ������ĵ�һ������������n,m,(1��n,m��10)��ʾ������к��� �Ժ��n�У�ÿ��m��������ÿ�������ľ���ֵ������100�����뱣֤A��B�ǿɳ˵ġ�

���
���ÿ�������Ľ�����󣬾��������֮����һ���ո��������β�޿ո�

��������
2
2 2
1 1
1 1
2 1
1
1
2 2
1 1
1 1
2 2
1 1
1 0

�������
2
2
2 1
2 1*/

				

