/*アルゴリズムと工夫点(素数洞穴/CPU: 20 ms Memory: 34532 KB  Length: 3171 B)
dp[a]:洞窟番号aの洞窟に到達した時の，それまで通過した素数洞窟の最大数 とする動的計画法で解ける．
渦を巻くように番号付けられた洞窟の状態を二次元配列で表したものをmmapとする．
mmapにおいて，番号aの洞窟への1つ前の移動元洞窟の番号が{x,y,z}である時，dp[a]=max(dp[x],dp[y],dp[z]) となる．

前処理:
1.まず，値が1ずつ増えていく螺旋状の数列を二次元配列mmapを求めておく(initMap)
この時，洞窟番号に対するmmap上の座標も(id2Y,id2X) として求めておく．
最悪計算量は O(MAX_M)<10^7
2.また，エラトステネスの篩を用いた素数判定を行う1次元配列isPrime を求めておく(init)
最悪計算量は O(MAX_M*log(log(MAX_M)))≒10^6

本処理:
dpテーブルの値を埋めていく．遷移は「配るDP」で．値を埋めていく順番はBFSそのものであるから，それを利用する．
1つのテストケースに対する最悪計算量は O(m)≒10^6
※重実装の良問だった
*/
#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_M (int)(1e6)
using namespace std;

typedef pair<int,int> P;

int m,n;
vector<vector<int> > mmap(2*(int)sqrt(MAX_M),vector<int>(2*(int)sqrt(MAX_M),MAX_M+1));
vector<int> id2Y(MAX_M+1),id2X(MAX_M+1);

void initMap(){
    int i,id=1,dis=1,now=0,y=(int)mmap.size()/2,x=(int)mmap.size()/2;
    const int dy[]={0,-1,0,1},dx[]={1,0,-1,0},MAX_D=4;
    mmap[y][x]=id;
    id2Y[id]=y;id2X[id]=x;
    id++;
    while(1){
        i=dis;
        while(i--){
            y+=dy[now];x+=dx[now];
            mmap[y][x]=id;
            id2Y[id]=y;id2X[id]=x;
            id++;
            if(id>MAX_M)return ;
        }
        now=(now+1)%MAX_D;
        i=dis;
        while(i--){
            y+=dy[now];x+=dx[now];
            mmap[y][x]=id;
            id2Y[id]=y;id2X[id]=x;
            id++;
            if(id>MAX_M)return ;
        }
        now=(now+1)%MAX_D;
        dis++;
    }
}

vector<bool> init(){
    int i,j;
    vector<bool> isPrime(MAX_M+1,true);
    isPrime[0]=isPrime[1]=false;
    for(i=2;i<=MAX_M;i++){
        if(isPrime[i]){
            j=2*i;
            while(j<=MAX_M){
                isPrime[j]=false;
                j+=i;
            }
        }
    }
    return isPrime;
}

int main(){
    int i,j;
    initMap();
    P ans;
    vector<bool> isPrime=init();
    vector<int> visited,lastPrime;
    const int dy[]={1,1,1},dx[]={-1,0,1},MAX_D=3,NIL=-1;
    auto bfs=[&](int now)->P{
        int i,j,y,x;
        P ans;
        queue<int> que;
        visited[now]=isPrime[now];
        lastPrime[now]=isPrime[now]?now:0;
        ans=P(visited[now],lastPrime[now]);
        que.push(now);
        while(que.size()){
            now=que.front();que.pop();
            rep(i,MAX_D){
                y=id2Y[now]+dy[i];x=id2X[now]+dx[i];
                if(0<=y&&y<(int)mmap.size()&&0<=x&&x<(int)mmap.size()&&mmap[y][x]<=m){
                    if(visited[mmap[y][x]]==NIL)que.push(mmap[y][x]);
                    if(visited[mmap[y][x]]<visited[now]+isPrime[mmap[y][x]]){
                        visited[mmap[y][x]]=visited[now]+isPrime[mmap[y][x]];
                        lastPrime[mmap[y][x]]=isPrime[mmap[y][x]]?mmap[y][x]:lastPrime[now];
                    }else if((!isPrime[mmap[y][x]])&&visited[mmap[y][x]]==visited[now]+isPrime[mmap[y][x]]){
                        lastPrime[mmap[y][x]]=max(lastPrime[mmap[y][x]],lastPrime[now]);
                    }
                    if(ans.first<visited[mmap[y][x]])ans=P(visited[mmap[y][x]],lastPrime[mmap[y][x]]);
                    else if(ans.first==visited[mmap[y][x]])ans.second=max(ans.second,lastPrime[mmap[y][x]]);
                }
            }
        }
        return ans;
    };
    //for(i=(int)mmap.size()/2-10;i<(int)mmap.size()/2+10;i++){for(j=(int)mmap.size()/2-10;j<(int)mmap.size()/2+10;j++)printf("%3d ",mmap[i][j]);puts("");}return 0;
    while(1){
        scanf("%d%d",&m,&n);
        if(!(m||n))break;
        visited=vector<int>(m+1,NIL);
        lastPrime=vector<int>(m+1,NIL);
        ans=bfs(n);
        printf("%d %d\n",ans.first,ans.second);
    }
    return 0;
}