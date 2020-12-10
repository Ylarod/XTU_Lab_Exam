// Problem: 1132
// Solution: 1915535
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1152KB





						
#include <stdio.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--){
    char a[10],b[10];
    scanf("%s %s",&a,&b);
    if(a[0]=='z'){
        a[0]=0;
    }else if(a[0]=='o'){
        a[0]=1;
    }else if(a[0]=='t'){
        if(a[1]=='w') a[0]=2;
        else a[0]=3;
    }else if(a[0]=='f'){
        if(a[1]=='o') a[0]=4;
        else a[0]=5;
    }else if(a[0]=='s'){
        if(a[1]=='i') a[0]=6;
        else a[0]=7;
    }else if(a[0]=='e'){
        a[0]=8;
    }else if(a[0]=='n'){
        a[0]=9;
    }
    if(b[0]=='z'){
        b[0]=0;
    }else if(b[0]=='o'){
        b[0]=1;
    }else if(b[0]=='t'){
        if(b[1]=='w') b[0]=2;
        else b[0]=3;
    }else if(b[0]=='f'){
        if(b[1]=='o') b[0]=4;
        else b[0]=5;
    }else if(b[0]=='s'){
        if(b[1]=='i') b[0]=6;
        else b[0]=7;
    }else if(b[0]=='e'){
        b[0]=8;
    }else if(b[0]=='n'){
        b[0]=9;
    }
    printf("%d\n",a[0]+b[0]);
    }
    return 0;
}

				

