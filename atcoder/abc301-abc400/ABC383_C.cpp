/*アルゴリズムと工夫点(Humidifier 3/CPU: 30 ms Memory: 11272 KB  Length: 1275 B)
始点が複数ある場合のBFSは「多始点BFS」と呼ばれ，初期化の処理が通常のBFSと異なる．
始点を全て列挙し，距離テーブルの更新(dist[yi][xi]=0)を終えてから，全てキューに追加してから，通常のBFSを行えばよい．
最悪計算量は O(H*W)<10^7 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int h,w,d;

int main(){
    int i,j;
    scanf("%d%d%d",&h,&w,&d);
    vector<string> mmap(h);
    rep(i,h)cin>>mmap[i];
    const int NIL=-1,dy[]={-1,0,1,0},dx[]={0,1,0,-1},MAX_D=4;
    auto bfs=[&]()->int{
        int i,j,y,x,ans=0;
        P now;
        vector<vector<int> > dist(h,vector<int>(w,NIL));
        queue<P> que;
        rep(i,h)rep(j,w)if(mmap[i][j]=='H'){
            dist[i][j]=0;
            mmap[i][j]='#';
            ans++;
            que.push(P(i,j));
        }
        while(que.size()){
            now=que.front();que.pop();
            if(dist[now.first][now.second]>=d)break;
            rep(i,MAX_D){
                y=now.first+dy[i];
                x=now.second+dx[i];
                if(0<=y&&y<h&&0<=x&&x<w&&mmap[y][x]=='.'){
                    mmap[y][x]='#';
                    dist[y][x]=dist[now.first][now.second]+1;
                    ans++;
                    que.push(P(y,x));
                }
            }
        }
        return ans;
    };
    printf("%d\n",bfs());
    return 0;
}