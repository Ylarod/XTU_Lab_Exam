// Problem: 1293
// Solution: 1913834
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1156KB





						
#include <stdio.h>
int main()
{
        int k,n,a,b,c,hs;
        scanf("%d",&k);
        while(k--){
                int count1,count,hs=1,ch0=64,ch;
                scanf("%d",&n);
                a=n;
                ch0 += n;
                ch = ch0;
                for(ch=ch0;hs<=n;hs++){
                        ch = ch0;
for(count=0;count<n-hs;count++){
        printf(" ");
}
for(count1=1;count1<hs;ch--){
        printf("%c",ch);
        count1++;
}
for(count1=0;count1<hs;count1++)
{
        printf("%c",ch);
        ch++;
}
printf("\n");
}
hs--;
hs--;
for(ch=ch0;hs>0;hs--){
                        ch = ch0;
for(count=0;count<n-hs;count++){
        printf(" ");
}
for(count1=1;count1<hs;ch--){
        printf("%c",ch);
        count1++;
}
for(count1=0;count1<hs;count1++)
{
        printf("%c",ch);
        ch++;
}
printf("\n");
}
}
return 0;
}
				

