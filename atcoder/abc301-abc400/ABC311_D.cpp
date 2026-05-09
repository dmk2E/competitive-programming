/*アルゴリズムと工夫点(Grid Ice Floor/CPU: 2 ms Memory: 3984 KB  Length: 1342 B)
BFSを応用して解く．
ある氷の位置から上下左右に一度でも移動をしたことがある場合，もう一度その場所から出発する必要はない．
従って停止したことがあるか否か，を保持するフラグ配列を用意し，停止する可能があるマスを頂点とする無向グラフ上でBFSをすればよい．
通過したマスを数え上げるため，それ専用のフラグ配列も用意しておく．
最悪計算量は，O(N*M*(N+M))<10^7 となり高速．
※ 公式解説ではプレイヤ自身に複数の情報を付け加え，その状態によって頂点間遷移を管理することで，O(N*M)での実装をしていた．
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

int n,m;

int main(){
    int i,j,ans=0;
    scanf("%d%d",&n,&m);
    vector<string> mp(n);
    rep(i,n)cin>>mp[i];
    const int dy[]={-1,0,1,0},MAX_D=4;
    const int dx[]={0,1,0,-1};
    vector<vector<bool> > vis(n,vector<bool>(m,false)),is_stopped(n,vector<bool>(m,false));
    queue<P> que;
    vis[1][1]=true;is_stopped[1][1]=true;
    que.push(P(1,1));
    ans++;
    while(que.size()){
        P now=que.front();que.pop();
        rep(i,MAX_D){
            P nxt(now.first+dy[i],now.second+dx[i]);
            if(mp[nxt.first][nxt.second]=='.'){
                while(mp[nxt.first][nxt.second]=='.'){
                    if(vis[nxt.first][nxt.second]==false)ans++,vis[nxt.first][nxt.second]=true;
                    nxt=P(nxt.first+dy[i],nxt.second+dx[i]);
                }
                nxt=P(nxt.first-dy[i],nxt.second-dx[i]);
                if(is_stopped[nxt.first][nxt.second]==false){
                    is_stopped[nxt.first][nxt.second]=true;
                    que.push(nxt);
                }
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}