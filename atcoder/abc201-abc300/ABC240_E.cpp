/*アルゴリズムと工夫点(Ranges on Tree/CPU: 144 ms Memory: 25820 KB  Length: 1079 B)
ans[i]:Siに対応する[l,r] とし，オイラーツアーで各ans[i]を求めていく深さ優先探索で解く．
木DP?みたいな処理．
根付き木の子には，l=rとなるような現時点で割り当てていない最小の[l,r]を割り当て，根，および葉は子を含む最小の長さとなる[l,r]を割り当てていけばよい．
最悪計算量は O(N)<10^6 となり，十分高速．
※初見5完!
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n;

int main(){
    int i,j,k;
    scanf("%d",&n);
    vector<vector<int> > adj(n);
    rep(i,n-1){
        scanf("%d%d",&j,&k);
        j--;k--;
        adj[j].push_back(k);
        adj[k].push_back(j);
    }
    vector<P> ans(n);
    const int MIN=-1,MAX=n;
    auto dfs=[&](auto& f,int par,int now,int& mx)->P{
        int i;
        P aans=P(MAX,MIN),tmp;
        rep(i,adj[now].size()){
            if(adj[now][i]!=par){
                tmp=f(f,now,adj[now][i],mx);
                aans.first=min(aans.first,tmp.first);
                aans.second=max(aans.second,tmp.second);
            }
        }
        if(aans.first==MAX&&aans.second==MIN){
            aans=P(mx,mx);
            mx++;
        }
        return ans[now]=aans;
    };
    i=0;
    dfs(dfs,MIN,0,i);
    rep(i,n)printf("%d %d\n",ans[i].first+1,ans[i].second+1);
    return 0;
}