/*アルゴリズムと工夫点(A Path in A Dictionary/CPU: 188 ms Memory: 4672 KB  Length: 1651 B)
辞書順の定義より，できるだけ番号が小さい頂点を訪問していけばよい．
ただし，進んだ頂点から，頂点yに到達可能か否かを高速に判定する必要がある．
そこで次の頂点に進む前に，頂点yからBFSを行い，その頂点に進んで良いか判定しておく．
従って，一つのテストケース当たりの最悪計算量は，O(N*(N+M))<10^8 となり間に合う．
※ パス：同じ頂点を通らない経路
※ 辞書順：ある列S, Tが存在する時，S<T ⇔ 前から巡回した時，初めて登場した異なる要素について，S[i]<T[i] となる || TはSを接頭部分文字列として持つ
*/
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;

void solve(){
    int n,m,x,y,i,j;
    const int NIL=-1;
    scanf("%d%d%d%d",&n,&m,&x,&y);
    x--;y--;
    vector<vector<int> > adj(n);
    while(m--){
        scanf("%d%d",&i,&j);
        i--;j--;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    queue<int> que;
    vector<int> par(n,NIL);
    vector<bool> is_valid;
    auto bfs=[&]()->void{
        int i;
        is_valid=vector<bool>(n,false);
        queue<int> que;
        que.push(y);
        is_valid[y]=true;
        while(que.size()){
            int now=que.front();que.pop();
            for(int nxt:adj[now]){
                if(par[nxt]==NIL&&is_valid[nxt]==false){
                    is_valid[nxt]=true;
                    que.push(nxt);
                }
            }
        }
    };
    que.push(x);
    par[x]=x;
    while(que.size()){
        int min_id=n,now=que.front();que.pop();
        bfs();
        for(int nxt:adj[now])if(is_valid[nxt]&&par[nxt]==NIL)min_id=min(min_id,nxt);
        par[min_id]=now;
        que.push(min_id);
        if(min_id==y)break;
    }
    vector<int> ans;
    i=y;
    while(par[i]!=i){
        ans.push_back(i+1);
        i=par[i];
    }
    ans.push_back(i+1);
    reverse(ans.begin(),ans.end());
    rep(i,ans.size()-1)printf("%d ",ans[i]);printf("%d\n",ans[i]);
}

int main(){
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}