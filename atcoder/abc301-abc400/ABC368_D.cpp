/*アルゴリズムと工夫点(Minimum Steiner Tree/CPU: 180 ms Memory: 24328 KB  Length: 1143 B)
dp[i]:頂点iを頂点とする部分木に含まれるvの要素の数
とする木DPで解ける．実装はDFSで．DFSを始める最初の頂点は，Vに含まれる要素とすること．
*/
#include<iostream>
#include<vector>
#include<set>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,k;
vector<int> dp;

int main(){
    int i,j,ii;
    const int NIL=-1;
    scanf("%d%d",&n,&k);
    vector<vector<int> > adj(n,vector<int>(0));
    set<int> v;
    dp=vector<int>(n,NIL);
    //vector<bool> isRoot(n,true);
    rep(i,n-1){
        scanf("%d%d",&ii,&j);
        ii--;j--;
        adj[ii].push_back(j);
        adj[j].push_back(ii);
    }
    rep(i,k){
        scanf("%d",&ii);
        ii--;
        v.insert(ii);
    }
    auto dfs=[&](auto& f,int par,int now)->int{
        int i,cnt=0;
        if(v.find(now)!=v.end())cnt++;
        rep(i,adj[now].size()){
            if(adj[now][i]!=par){
                cnt+=f(f,now,adj[now][i]);
            }
        }
        dp[now]=cnt;
        return cnt;
    };
    rep(i,n)if(v.find(i)!=v.end())break;
    dfs(dfs,-1,i);
    ii=0;
    rep(i,n){
        //printf("%d ",dp[i]);
        if(dp[i]>0)ii++;
    }
    //puts("");
    printf("%d\n",ii);
    return 0;
}