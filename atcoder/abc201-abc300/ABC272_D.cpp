/*アルゴリズムと工夫点(Root M Leaper/CPU: 31 ms Memory: 5060 KB  Length: 1126 B)
N<=400 と小さいから，マス目を配列として持てるから，各マスを頂点とみなしたグラフにおけるBFSで解く．
問題は辺の張り方だが，これは(k,l)を固定した時の (i-k)^2+(j-l)^2=M を満たす(i,j)の候補を予め求めておく．
具体的には，(k,l)=(0,0) とした時の上式を満たす(i,j)を，(dy,dx)として求めておけばよい．
最悪計算量は，O(M+N^2)<10^7 より高速．
*/
#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n,m;

int main(){
    int i,j,k,y,x;
    scanf("%d%d",&n,&m);
    vector<int> dy,dx;
    k=(int)sqrt(m)+1;
    for(i=-k;i<=k;i++){
        for(j=-k;j<=k;j++){
            if(m==i*i+j*j){
                dy.push_back(i);
                dx.push_back(j);
            }
        }
    }
    const int NIL=-1;
    vector<vector<int> > dist(n,vector<int>(n,NIL));
    queue<P> que;
    P now;
    que.push(P(0,0));
    dist[0][0]=0;
    while(que.size()){
        now=que.front();que.pop();
        rep(i,dy.size()){
            y=now.first+dy[i];
            x=now.second+dx[i];
            if(0<=y&&y<n&&0<=x&&x<n&&dist[y][x]==NIL){
                que.push(P(y,x));
                dist[y][x]=dist[now.first][now.second]+1;
            }
        }
    }
    rep(i,n){
        rep(j,n-1)printf("%d ",dist[i][j]);
        printf("%d\n",dist[i][j]);
    }
    return 0;
}