// Problem: 1128
// Solution: 1876314
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1160KB





						
#include<stdio.h>
int main()
{
    int n; 
    while(scanf("%d",&n)!=EOF&&n!=0) 
    {
        int sum=0;
        int score,i;
        for(i=0;i<n;i++)
        {
            scanf("%d",&score); 
            if(score<60) sum++; 
            else          continue;
        }
        printf("%d\n",sum);  
    }
    return 0;
}
				

