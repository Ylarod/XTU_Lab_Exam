// Problem: 1112
// Solution: 1872605
// Language: G++
// Result: Accepted
// Time: 15MS
// Memory: 1164KB





						
#include <stdio.h>
int main ()
{
int xi,xii,yi,yii,ai,aii,bi,bii,end,xiii,yiii,n;
scanf("%d",&n);
while (n>0){
scanf("%d %d",&xi,&yi);
scanf("%d %d",&xii,&yii);
scanf("%d %d",&xiii,&yiii);
ai=xii-xi;
bi=yii-yi;
aii=xiii-xi;
bii=yiii-yi;
end=ai*bii-bi*aii;
if (end==0)
printf("Yes\n");
else
printf("No\n");
n--;
}
return 0;
}

				

