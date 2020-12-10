// Problem: 1142
// Solution: 1876259
// Language: G++
// Result: Accepted
// Time: 312MS
// Memory: 1388KB





						
#include<bits/stdc++.h>
using namespace std;
int main()
{    int n; 
   while(scanf("%d",&n),n)    {
        int cnt=0; 
       int pos=1;       
 do       
 {            if(pos<=n) pos*=2;
            else pos=(pos*2-1)%(2*n);
           cnt++;        }    while(pos!=1);
        printf("%d\n",cnt);    }  
  return 0;}
				

