/*アルゴリズムと工夫点(Takahashi is Slime 2/CPU: 69 ms Memory: 9488 KB  Length: 1636 B)
優先度付きキューを用いたBFSのようなシミュレーションで解く．
各スライムを既にキューに入れたかをflagで保持しつつ，優先度付きキューに，今現在隣接しているスライムSijを(i,j,Sij)の形で保持しつつ，条件を満たす時に限り領域を広げていく．
領域を広げる際，隣接しているスライムが増えるので，flagを考慮しつつ，追加すればよい．
最悪計算量は O(H*W*log2(H*W))<10^7 となり高速．
*/
#include<iostream>
#include<queue>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Data{
    int y,x;
    ll s;

    Data(int yy=0,int xx=0,ll ss=0):y(yy),x(xx),s(ss){}

    bool operator<(const Data& k)const{
        return s>k.s||(s==k.s&&(y==k.y?x<k.x:y<k.y));
    }
};

int h,w;
ll X;

int main(){
    int i,j,p,q;
    scanf("%d%d%lld",&h,&w,&X);
    vector<vector<ll> > s(h,vector<ll>(w));
    scanf("%d%d",&p,&q);p--;q--;
    rep(i,h)rep(j,w)scanf("%lld",&s[i][j]);
    const int dy[]={-1,0,1,0},dx[]={0,1,0,-1},MAX_D=4;
    auto bfs=[&](int y,int x)->ll{
        int i,j,k;
        Data now;
        ll power=s[y][x];
        vector<vector<bool> > flag(h,vector<bool>(w,false));
        priority_queue<Data> PQ;
        flag[y][x]=true;
        rep(k,MAX_D){
            i=y+dy[k];
            j=x+dx[k];
            if(0<=i&&i<h&&0<=j&&j<w&&flag[i][j]==false){
                flag[i][j]=true;
                PQ.push(Data(i,j,s[i][j]));
            }
        }
        while(PQ.size()&&(PQ.top().s)<(power+X-1)/X){
            now=PQ.top();PQ.pop();
            //printf("power:%lld (%d,%d)\n",power,now.y,now.x);
            power+=now.s;
            rep(i,MAX_D){
                y=now.y+dy[i];
                x=now.x+dx[i];
                if(0<=y&&y<h&&0<=x&&x<w&&flag[y][x]==false){
                    PQ.push(Data(y,x,s[y][x]));
                    flag[y][x]=true;
                }
            }
        }
        return power;
    };
    printf("%lld\n",bfs(p,q));
    return 0;
}