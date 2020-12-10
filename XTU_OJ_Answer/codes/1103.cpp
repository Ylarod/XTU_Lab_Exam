// Problem: 1103
// Solution: 1895819
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1160KB





						
#include<stdio.h>
int main()
{
    int year,month,day;
    int k;
    scanf("%d",&k);
    while(k--)
    {
        int sum=0;
        scanf("%d-%d-%d",&year,&month,&day);
        switch(month) 
        {
            case 1:sum=0; break;
            case 2:sum=31;break;
            case 3:sum=59;break;
            case 4:sum=90;break;
            case 5:sum=120;break;
            case 6:sum=151;break;
            case 7:sum=181;break;
            case 8:sum=212;break;
            case 9:sum=243;break;
            case 10:sum=273;break;
            case 11:sum=304;break;
            case 12:sum=334;break;
        }
        sum+=day;
        if(((year%400==0)||(year%4==0&&year%100!=0))&&month>2) 
        {
            sum++;
        }
        printf("%d\n",sum);
    }
    return 0;
}

				

