// Problem: 1230
// Solution: 1964448
// Language: G++
// Result: Accepted
// Time: 78MS
// Memory: 1252KB





						
#include<stdio.h>
int main(){
    int n,m,x,y;
    char s[7];
    while(~scanf("%d%d",&n,&m)){
        scanf("%s",s);
        x=(n+m)/2;
        y=n-x;
        if(n<m) printf("Impossible\n");
        else if(x-y!=m) printf("Impossible\n");
        else if(n>=m&&x-y==m) {
            if(s[0]=='A'&&m) printf("%d:%d\n",x,y);//×¢ÒâmÖµ 
            else if(s[0]=='B'&&m) printf("%d:%d\n",y,x);// 
            else if(s[0]=='D'&&!m) printf("%d:%d\n",x,y);// 
            else printf("Impossible\n");
        }
        else printf("Impossible\n");
        
    }
    return 0;
}
				

