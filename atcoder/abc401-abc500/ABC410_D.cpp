/*アルゴリズムと工夫点(XOR Shortest Walk/CPU: 10 ms Memory: 4156 KB  Length: 1176 B)
拡張BFSで解く．
各頂点について，その頂点に到達した時の累積XORの値としてあり得るパターン数分だけ頂点を拡張したグラフ上で，深さ優先探索や幅優先探索をする．
その後，あり得る累積XORの値の中の最小値を出力すればよい．
最悪計算量は，O((N+M)*max(Wi))<10^7 となり高速．
※自分は拡張BFSと呼んでいるが，俗には「頂点倍化」というらしい
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_DIGIT 10
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;//(to,cost)

int n,m;

int main(){
    int i,j,k,ans;
    scanf("%d%d",&n,&m);
    vector<vector<P> > adj(n);
    while(m--){
        scanf("%d%d%d",&i,&j,&k);
        i--;j--;
        adj[i].push_back(P(j,k));
    }
    auto bfs=[&]()->int{
        P now;
        const int INF=1<<MAX_DIGIT;
        vector<vector<bool> > vis(n,vector<bool>(INF,false));
        queue<P> que;//(to,state)
        vis[0][0]=true;
        que.push(P(0,0));
        while(que.size()){
            now=que.front();que.pop();
            for(P e:adj[now.first]){
                if(vis[e.first][now.second^e.second]==false){
                    vis[e.first][now.second^e.second]=true;
                    que.push(P(e.first,now.second^e.second));
                }
            }
        }
        int i;
        rep(i,INF)if(vis[n-1][i])break;
        return i==INF?-1:i;
    };
    printf("%d\n",bfs());
    return 0;
}