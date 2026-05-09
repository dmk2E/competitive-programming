/*アルゴリズムと工夫点(Number of Routes/CPU: 1 ms Memory: 3956 KB  Length: 544 B)
最短移動しかしないから，BFSするまでもなく，ループを用いた動的計画法で解く．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w;

int main(){
    int i,j;
    scanf("%d%d",&h,&w);
    vector<vector<ll> > dp(h,vector<ll>(w,0));
    dp[0][0]=1;
    vector<string> mmap(h);
    rep(i,h)cin>>mmap[i];
    rep(i,h)rep(j,w){
        if(i+1<h&&mmap[i+1][j]=='.')dp[i+1][j]+=dp[i][j];
        if(j+1<w&&mmap[i][j+1]=='.')dp[i][j+1]+=dp[i][j];
    }
    printf("%lld\n",dp[h-1][w-1]);
    return 0;
}