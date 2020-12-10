// Problem: 1117
// Solution: 1877684
// Language: G++
// Result: Accepted
// Time: 281MS
// Memory: 1160KB





						
#include <stdio.h>
int main()
{
int n,a,b,c,he,zheng,yu,count;
scanf("%d",&n);
while(n--){
scanf("%d %d %d",&a,&b,&c);
//printf("%d\n",a);printf("%d\n",b);printf("%d\n",c);
for(count=0;a<=b;a++){
    zheng=a;
he=0;
    while (zheng){
    yu=zheng%10;
    zheng=zheng/10;
he=yu*yu+he;
}
//printf("%d\n",he);
he=he%10;
if(he==c)
count++;
}
printf("%d\n",count);
//n--;
}
return 0;
}
				

