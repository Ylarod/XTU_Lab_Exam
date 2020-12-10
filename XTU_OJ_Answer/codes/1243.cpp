// Problem: 1243
// Solution: 1965618
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1252KB





						
#include <stdio.h>
#include <string.h>
int bb[15];
int judge(int a,int b)
{
    a -= 48;
    b -=48;
    if(a==5)
        return 1;
    else {
        if(b==5)
    {
        return 1;
    }else{
        if(a%2==1)
        {
            if(b%2==1)
            {
                if(bb[(a+b)/2])
                    return 1;
                else
                    return 0;
            }else
            return 1;
        }else{
            if((b+a)!=10)
                return 1;
            else
            {
                if(bb[5])
                    return 1;
                else
                    return 0;
            }
        }
    }
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        char a[15],lena,i,j,n,flag;
        for(i=0;i<11;i++)
        {
            bb[i] = 0;
        }
        scanf("%s",a);
        lena = strlen(a);
       // printf("lena:%d\n",lena);
        if(lena==1){printf("Yes\n"); continue;}
        bb[a[0]-48] = 1;
        for(i=0;i<lena-1;i++)
        {
         //   printf("%d\n",i);
            flag = judge(a[i],a[i+1]);
          //  printf("flag:%d",flag);
            if(flag==0)
                break;
            else
            bb[a[i+1]-48] = 1;
        }
        if(flag) printf("Yes\n");
        else printf("No\n");
    }
}

				

