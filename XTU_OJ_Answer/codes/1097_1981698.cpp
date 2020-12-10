// Problem: 1097
// Solution: 1981698
// Language: G++
// Result: Accepted
// Time: 30MS
// Memory: 1256KB





						
#include<stdio.h>
#include<string.h>
int main()
{
    int a[1100]={0};
    int k;
    scanf("%d",&k);
    while(k--){
        char s;
        int i;
        scanf("%d",&i);
        getchar();
        s=getchar();
        int m;
        for(m=0;m<i;m++){
        scanf("%d",&a[m]);
        }
            int x,y;
            int t;
        if(s=='A'){
            for(x=0;x<i;x++){
                for(y=x+1;y<i;y++){
                    if(a[x]>a[y]){
                        t=a[x];
                        a[x]=a[y];
                        a[y]=t;
                        
                    }
                }
            }
        }
        if(s=='D'){
            for(x=0;x<i;x++){
                for(y=x+1;y<i;y++){
                    if(a[y]>a[x]){
                        t=a[x];
                        a[x]=a[y];
                        a[y]=t;
            
        }
    }
 }
}
        int w;
        for(w=0;w<i-1;w++){
            printf("%d ",a[w]);
        }
        printf("%d",a[i-1]);
        printf("\n");
        }
        return 0;
    }
				

