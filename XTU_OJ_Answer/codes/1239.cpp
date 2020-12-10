// Problem: 1239
// Solution: 1968635
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1260KB





						
#include <stdio.h>
int main()
{
    /*逻辑：按行扫描 碰见零则左移一位（一行最多挪四次不然若后面全是零会死循环）若不是零则新开一个循环往下扫描扫到不是零相等就加上不等就放到后一位 被扫到的数清零 扫到第四位仍是零则对第四位进行如上操作*/
    int a[7][7],i,j;
    int cishu;
    char order[10];
    int k;
    scanf("%d",&k);
    getchar();
    while(k--)
    {
        for(i=1;i<5;i++)
            for(j=1;j<5;j++)
            scanf("%d",&a[i][j]);
        scanf("%s",order);
        getchar();
        int k,j1,i1;
        if(order[0]== 'L')
        {
            for(i=1;i<5;i++)
            {
                cishu = 0;
                for(j=1;j<4;j++)
                {
                    if(a[i][j])
                    {
                        k = j;
                        do{
                            k++;
                        }while(k<4&&a[i][k]==0);
                        if(a[i][j]==a[i][k])
                        {
                            a[i][j] *= 2;
                            a[i][k] = 0;
                          // printf("  %d:%d",i,a[i][j]);
                        }else{
                            j1 = a[i][k];
                            a[i][k] = 0;
                            a[i][j+1] = j1;
                        }
                    }else{
                        for(j1=j;j1<4;j1++)
                        {
                            a[i][j1] = a[i][j1+1];
                        }
                        a[i][4] = 0;
                        if(cishu<3)
                            j--;
                        cishu++;
                    }
                }
            }
        }
        if(order[0]=='R')
        {
            for(i=1;i<5;i++)
            {
                cishu = 0;
                for(j=4;j>1;j--)
                {
                    if(a[i][j])
                    {
                        k = j;
                        do{
                            k--;
                        }while(k>1&&a[i][k]==0);
                        //printf("wtf%d,%d.%d:%d\n",k,i,j,a[i][j]);
                        if(a[i][j]==a[i][k])
                        {
                            a[i][j] *= 2;
                            a[i][k] = 0;
                          // printf("%d,%d.%d:%d\n",k,i,j,a[i][j]);
                        }else{
                            j1 = a[i][k];
                            a[i][k] = 0;
                            a[i][j-1] = j1;
                        }
                    }else{
                        for(j1=j;j1>1;j1--)
                        {
                            a[i][j1] = a[i][j1-1];
                        }
                        a[i][1] = 0;
                        if(cishu<3)
                            j++;
                        cishu++;
                    }
                }
            }
        }
        if(order[0]=='U')
        {
            for(j=1;j<5;j++)
            {
                    cishu = 0;
                for(i=1;i<4;i++)
                {
                    if(a[i][j])
                    {
                        k = i;
                        do{
                            k++;
                        }while(k<4&&a[k][j]==0);
                        if(a[i][j]==a[k][j])
                        {
                            a[i][j] *= 2;
                            a[k][j] = 0;
                        }else{
                            j1 = a[k][j];
                           // printf("%d.%d:%d  ",k,j,a[k][j]);
                            a[k][j] = 0;
                            a[i+1][j] = j1;
                        }
                    }else{
                        for(j1=i;j1<4;j1++)
                        {
                            a[j1][j] = a[j1+1][j];
                        }
                        a[4][j] = 0;
                        if(cishu<3)
                            i--;
                        cishu++;
                    }
                }
            }
        }
        if(order[0]=='D')
        {
            for(j=1;j<5;j++)
            {
                    cishu = 0;
                   // printf("1\n");
                for(i=4;i>1;i--)
                {//printf("2\n");
                    if(a[i][j])
                    {
                        k = i;
                        do{
                            k--;
                        }while(k>1&&a[k][j]==0);
                        if(a[i][j]==a[k][j])
                        {
                            a[i][j] *= 2;
                            a[k][j] = 0;
                        }else{
                            j1 = a[k][j];
                          //  printf("%d.%d:%d  ",k,j,a[k][j]);
                            a[k][j] = 0;
                            a[i-1][j] = j1;
                        }
                    }else{
                        for(j1=i;j1>1;j1--)
                        {
                            a[j1][j] = a[j1-1][j];
                           // printf("3\n");
                        }
                        a[1][j] = 0;
                        if(cishu<3)
                            i++;
                        cishu++;
                    }
                }
            }
        }
        for(i=1;i<5;i++){
            for(j=1;j<5;j++)
        {
            if(j!=1)
                printf(" ");
            printf("%d",a[i][j]);
        }
        printf("\n");
        }
        printf("\n");
    }
    return 0;
}

				

