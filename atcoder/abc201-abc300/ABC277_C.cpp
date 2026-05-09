/*アルゴリズムと工夫点(Ladder Takahashi/CPU: 184 ms Memory: 28324 KB  Length: 2439 B)
各階を頂点，梯子を各頂点をつなぐ辺とみなした有向重み無しグラフと捉え，BFSにより頂点の最大番号を探索すればよい．
階の数が大きすぎるから座標圧縮を行うこと．最悪計算量はO(N*log2(N))<10^7 となり，高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> p;

typedef class CoordinateCompression{
    int MIN_X,MAX_X;
    bool initialized;
    vector<int> xs;
public:
    CoordinateCompression(int mmin=0,int mmax=(int)(1e9)+1):MIN_X(mmin),MAX_X(mmax),initialized(false){}
    
    void add(int x){
        if(MIN_X<=x&&x<=MAX_X)
            xs.push_back(x);
        initialized=false;
    }

    void init(){
        sort(xs.begin(),xs.end());
        xs.erase(unique(xs.begin(),xs.end()),xs.end());
        initialized=true;
    }

    int x2Id(int x){
        if(!initialized)init();
        int left=0,right=xs.size(),mid;
        while(left<right){
            mid=(left+right)/2;
            if(xs[mid]<x)
                left=mid+1;
            else
                right=mid;
        }
        return left;
    }

    int id2X(int id){
        if(!initialized)init();
        return xs[id];
    }

    int operator()(int x){
        return x2Id(x);
    }

    int operator[](int x){
        return id2X(x);
    }

    int size(){
        if(!initialized)init();
        return xs.size();
    }
}CC;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<p> ipt(n);
    CC xs;
    xs.add(1);
    rep(i,n){
        scanf("%d%d",&ipt[i].first,&ipt[i].second);
        xs.add(ipt[i].first);xs.add(ipt[i].second);
    }
    vector<vector<int> > adj(xs.size(),vector<int>(0));
    rep(i,n){
        ipt[i].first=xs(ipt[i].first);ipt[i].second=xs(ipt[i].second);
        adj[ipt[i].first].push_back(ipt[i].second);
        adj[ipt[i].second].push_back(ipt[i].first);        
    }
    auto bfs=[&]()->int{
        int i,mmax=xs(1),now;
        queue<int> que;
        vector<bool> visited(xs.size(),false);
        que.push(xs(1));
        visited[xs(1)]=true;
        while(que.size()){
            now=que.front();que.pop();
            rep(i,adj[now].size()){
                if(visited[adj[now][i]]==false){
                    visited[adj[now][i]]=true;
                    if(mmax<adj[now][i])mmax=adj[now][i];
                    que.push(adj[now][i]);
                }
            }
        }
        return mmax;
    };
    printf("%d\n",xs[bfs()]);
    return 0;
}