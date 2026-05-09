/*アルゴリズムと工夫点(Palindromic Shortest Path/CPU: 120 ms Memory: 4028 KB  Length: 1065 B)
回文の特性を考えると，真ん中から作っていくことを考えるとやりやすい．
<i>回文の長さが偶数なら，空文字列から考える．
<ii>回文の長さが奇数なら，ある1文字から考える．
これらを元に，頂点iから頂点jまでの条件を満たす最短距離の値を保持する頂点(i,j)を考え，多始点BFSを行えばよい．
最悪計算量は O(N^(4))≒10^8 となり間に合う．
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<string> adj(n);
    queue<P> que;
    rep(i,n)cin>>adj[i];
    const int NIL=-1;
    vector<vector<int> > dist(n,vector<int>(n,NIL));
    rep(i,n)dist[i][i]=0,que.push(P(i,i));
    rep(i,n)rep(j,i){
        if(adj[i][j]!='-')dist[i][j]=1,que.push(P(i,j));
        if(adj[j][i]!='-')dist[j][i]=1,que.push(P(j,i));
    }
    P now;
    while(que.size()){
        now=que.front();que.pop();
        rep(i,n)rep(j,n){
            if(adj[i][now.first]==adj[now.second][j]&&adj[now.second][j]!='-'&&dist[i][j]==NIL){
                dist[i][j]=dist[now.first][now.second]+2;
                que.push(P(i,j));
            }
        }
    }
    rep(i,n){
        rep(j,n-1)printf("%d ",dist[i][j]);
        printf("%d\n",dist[i][j]);
    }
    return 0;
}