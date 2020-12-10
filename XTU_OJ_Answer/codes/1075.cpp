// Problem: 1075
// Solution: 1850113
// Language: G++
// Result: Accepted
// Time: 0MS
// Memory: 1160KB





						
#include<stdio.h>

int main()

{



unsigned int u,v,r,s,i,d;



scanf("%u%u",&u,&v);

while(u !=0 && v!= 0)



{





d=u*v;



while(v!=0)



{
r=u%v;



u=v;



v=r;
}



printf("%u\n",d/u);

scanf("%u%u",&u,&v);

}



 return 0;
}

				

