/*アルゴリズムと工夫点(Sinking Land/CPU: 212 ms Memory: 18968 KB  Length: 1977 B)
標高が海面の高さ以下(c1)で，上下左右のどれかが「海または海に沈んだ区間」と隣接している(c2)場合，海に沈む．
まず，現在の海面の高さで，新たにどの区画が沈むのかを即座に求めるために，各区画を標高の高さの昇順にソートして持ち，海面の高さでシミュレーションする．
各区画の状態∈(T,C,F)とし，T=(c1,c2共に満たさない),C=(c1のみ満たす),F=(c1,c2共に満たす)=(沈んでいる)とする．
新たにc1を満たすか，海に沈んだりした区画の状態を，シミュレーションの際に更新する．この時，海に沈んだ場合，そこから隣接しているCの状態の区画は全てFになる．この操作はBFSで実装する．BFSでは，各区画の状態を保持している配列で
訪問済みか判定することで，無駄な探索を防止している．
最悪計算量はO(H*W*log2(H*W)+Y+H*W+H+W)=O(H*W*log2(H*W)+Y)<10^7 となり，高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_D 4
using namespace std;
typedef long long ll;

typedef enum state{
    T=1,
    C=0,
    F=-1
}State;

typedef struct data{
    int v,y,x;

    data(int vv=0,int yy=0,int xx=0):v(vv),y(yy),x(xx){}

    bool operator<(const data& k)const{
        return v<k.v;
    }
}Data;

int h,w,y;
const int dy[MAX_D]={1,0,-1,0},dx[MAX_D]={0,-1,0,1};
vector<vector<State> > mmap;
vector<Data> a;

int bfs(int y,int x){
    int i,j,cnt=0;
    queue<int> que;
    que.push(y*w+x);
    while(que.size()){
        y=que.front()/w;x=que.front()%w;que.pop();
        rep(i,MAX_D){
            if(y+dy[i]>=0&&y+dy[i]<h&&x+dx[i]>=0&&x+dx[i]<w&&mmap[y+dy[i]][x+dx[i]]==C){
                mmap[y+dy[i]][x+dx[i]]=F;
                cnt++;
                que.push((y+dy[i])*w+x+dx[i]);
            }
        }
    }
    return cnt;
}

void show(){
    int i,j;
    rep(i,h){
        rep(j,w)
            printf("%d ",mmap[i][j]);
        puts("");
    }
}

int main(){
    int i,j,k,sum;
    scanf("%d%d%d",&h,&w,&y);
    a=vector<Data>(h*w);
    mmap=vector<vector<State> >(h,vector<State>(w,T));
    rep(i,h){
        rep(j,w){
            scanf("%d",&a[i*w+j].v);
            a[i*w+j].y=i;a[i*w+j].x=j;
        }
    }
    sort(a.begin(),a.end());
    for(i=1,j=0,sum=h*w;i<=y;i++){
        while(j<a.size()&&a[j].v-i<=0){
            mmap[a[j].y][a[j].x]=C;
            rep(k,MAX_D){
                if(a[j].y+dy[k]<0||a[j].y+dy[k]>=h||a[j].x+dx[k]<0||a[j].x+dx[k]>=w||mmap[a[j].y+dy[k]][a[j].x+dx[k]]==F)
                    break;
            }
            if(k<MAX_D){
                mmap[a[j].y][a[j].x]=F;
                sum--;
                sum-=bfs(a[j].y,a[j].x);
            }
            j++;
        }
        //show();
        printf("%d\n",sum);
    }
    return 0;
}