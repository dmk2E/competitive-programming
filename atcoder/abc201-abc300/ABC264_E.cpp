/*アルゴリズムと工夫点(Blackout 2/CPU: 125 ms Memory: 11612 KB  Length: 1811 B)
N+M頂点の無向グラフと捉え，逆順にイベントをこなし，Union-Find木で解を求める．
一般に辺を切るより，辺を繋いでいく方が計算量は軽くなる．そこでイベントを逆時系列順にこなすことで，都市と発電所の連結成分を管理しながら解ける．
木内部で，各頂点が都市か発電所かのフラグを持っておくと実装しやすい．
最悪計算量は O((E+Q)*α(N+M+E))<10^7 となり高速．
※初見5完! 
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class UnionFindTree{
    int cnt;
    vector<int> par,rank,city;
    vector<bool> isEle;
public:
    UnionFindTree(int n=0,int m=0){
        rank=vector<int>(n+m,0);
        city=vector<int>(n+m,0);
        isEle=vector<bool>(n+m,false);
        cnt=0;
        int i;
        rep(i,n)city[i]=1;
        for(i=n;i<n+m;i++)isEle[i]=true;
        rep(i,n+m)par.push_back(i);
    }

    int root(int x){
        return par[x]==x?x:par[x]=root(par[x]);
    }

    void unite(int y,int x){
        y=root(y);
        x=root(x);
        if(y==x)return ;
        if(isEle[y]||isEle[x]){
            if(isEle[y]==false)cnt+=city[y];
            if(isEle[x]==false)cnt+=city[x];
        }
        if(rank[y]<rank[x]){
            par[y]=x;
            isEle[x]=(isEle[y]||isEle[x]);
            city[x]+=city[y];
        }else{
            par[x]=y;
            isEle[y]=(isEle[y]||isEle[x]);
            city[y]+=city[x];
            if(rank[y]==rank[x])rank[y]++;
        }
    }

    int ans(){
        return cnt;
    }
}UF;

int n,m,e,q;

int main(){
    int i,j;
    scanf("%d%d%d",&n,&m,&e);
    UF tree(n,m);
    vector<int> u(e),v(e);
    vector<bool> flag(e,true);
    rep(i,e){
        scanf("%d%d",&u[i],&v[i]);
        u[i]--;v[i]--;
    }
    scanf("%d",&q);
    vector<int> ans(q),x(q);
    rep(i,q){
        scanf("%d",&x[i]);
        x[i]--;
        flag[x[i]]=false;
    }
    rep(i,e)if(flag[i])tree.unite(u[i],v[i]);
    for(i=q-1;i>=0;i--){
        ans[i]=tree.ans();
        tree.unite(u[x[i]],v[x[i]]);
    }
    rep(i,q)printf("%d\n",ans[i]);
    return 0;
}