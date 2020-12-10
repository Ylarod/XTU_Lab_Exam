// Problem: 1248
// Solution: 1964034
// Language: G++
// Result: Accepted
// Time: 125MS
// Memory: 1252KB





						
#include <stdio.h>
int main()
{
    int k;
    scanf("%d",&k);
    while(k--)
    {
        int alice=0,bob=0,a1,a4,a2,a3,b1,b4,b2,b3,x,y,z;
        scanf("%d %d %d",&a4,&a2,&a3);
        scanf("%d %d %d",&b4,&b2,&b3);
      //  printf("%d %d %d\n",a4,a2,a3);
     //   printf("%d %d %d\n",b4,b2,b3);
        x = a4-a2;
        y = a2-a3;
        z = a3-a4;
      //  printf("X:%d Y:%d Z:%d\n",x,y,z);
        if(x==0)
        {
            if(a2==1) a2=7;
            if(a3==1) a3=7;
            if(a4==1) a4=7;
            if(y==0) alice = a4*100000;
            else alice = a2*1000+a3;
        }else if(y==0){
             if(a2==1) a2=7;
            if(a3==1) a3=7;
            if(a4==1) a4=7;
            alice = a2*1000+a4;
        }else if(z==0){
             if(a2==1) a2=7;
            if(a3==1) a3=7;
            if(a4==1) a4=7;
            alice = a4*1000+a2;
        }else{
            alice = a4+a2+a3;
        }
        //printf("alice:%d",alice);
        x = b4-b2;
        y = b2-b3;
        z = b3-b4;
       // printf("X:%d Y:%d Z:%d\n",x,y,z);
        if(x==0)
        {
            if(b2==1) b2=7;
            if(b3==1) b3=7;
            if(b4==1) b4=7;
            if(y==0) bob = b4*100000;
            else bob = b2*1000+b3;
        }else if(y==0){
            if(b2==1) b2=7;
            if(b3==1) b3=7;
            if(b4==1) b4=7;
            bob = b2*1000+b4;
        }else if(z==0){
             if(b2==1) b2=7;
            if(b3==1) b3=7;
            if(b4==1) b4=7;
            bob = b4*1000+b2;
        }else{
            bob = b4+b2+b3;
        }
     //   printf("bob:%d",bob);
      //  printf("A:%d B:%d",alice,bob);
        if(alice-bob>0) printf("Alice\n");
        else if(alice-bob==0) printf("Draw\n");
        else printf("Bob\n");
    }
    return 0;
}

				

