/*アルゴリズムと工夫点(1 2 1 3 1 2 1/CPU: 5 ms Memory: 4388 KB  Length: 650 B)

*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<vector<int> > memo(n+1);
    auto rec=[&](auto& f,int x)->void{
        if(x==1){memo[x].push_back(x);return ;}
        if(memo[x-1].size()==0)f(f,x-1);
        memo[x]=memo[x-1];
        memo[x].push_back(x);
        rep(i,memo[x-1].size())memo[x].push_back(memo[x-1][i]);
    };
    rec(rec,n);
    rep(i,memo[n].size()-1)printf("%d ",memo[n][i]);printf("%d\n",memo[n][i]);
    return 0;
}