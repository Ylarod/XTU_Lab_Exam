// Problem: 1258
// Solution: 1961757
// Language: G++
// Result: Accepted
// Time: 62MS
// Memory: 2268KB





						

#include<bits/stdc++.h>
using namespace std;
#define MAX 100
vector<int> P[MAX];
typedef char String[MAX];
 
 
void InitVector(int n)
{
    int n_count=1;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            P[i].push_back(n_count);
            n_count++;
        }
}
 
void Left(int a,int b)
{
    int temp[MAX];
    int length=P[a].size();
    b=b%length;
    for(int i=0; i<length; i++)
    {
 
        int flag=i;
        flag=(flag+length-b)%length;
        temp[flag]=P[a][i];
    }
    for(int i=0; i<length; i++) P[a][i]=temp[i];
}
 
void Right(int a,int b)
{
    int temp[MAX];
    int length=P[a].size();
    for(int i=0; i<length; i++)
    {
 
        int flag=i;
        flag=flag+b;
        flag=flag%length;
        temp[flag]=P[a][i];
    }
    for(int i=0; i<length; i++) P[a][i]=temp[i];
}
 
void Up(int a,int b,int n)//上减下加
{
    int temp[MAX];
    b=b%n;
    for(int i=0; i<n; i++)
    {
        int flag=i;
        flag=(flag+n-b)%n;
        temp[flag]=P[i][a];
    }
    for(int i=0; i<n; i++) P[i][a]=temp[i];
}
 
void Down(int a,int b,int n)//上减下加
{
    int temp[MAX];
    for(int i=0; i<n; i++)
    {
        int flag=i;
        flag=flag+b;
        flag=flag%n;
        temp[flag]=P[i][a];
    }
    for(int i=0; i<n; i++) P[i][a]=temp[i];
}
 
int main()
{
    int K;
    scanf("%d",&K);
    String Str;
    while(K--)
    {
        for(int i=0; i<MAX; i++) P[i].clear();
        int n,m;
        scanf("%d%d",&n,&m);
        InitVector(n);//初始化
        getchar();
        while(m--)
        {
            int num1,num2;
            char str_rec;
            gets(Str);
            sscanf(Str,"%c %d %d",&str_rec,&num1,&num2);
            if(str_rec=='L') Left(num1-1,num2);
            if(str_rec=='R') Right(num1-1,num2);
            if(str_rec=='U') Up(num1-1,num2,n);
            if(str_rec=='D') Down(num1-1,num2,n);
        }
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
            {
                if(i!=n-1) printf("%d ",P[i][j]);
                else printf(j==n-1?"%d":"%d ",P[i][j]);
            }
        printf("\n");
    }
    return 0;
}
				

