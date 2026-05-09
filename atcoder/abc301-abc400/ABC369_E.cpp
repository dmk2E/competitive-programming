/*アルゴリズムと工夫点(Sightseeing Tour/CPU: 196 ms Memory: 7628 KB  Length: 1850 B)
拡張ダイクストラ法で解こうとすると，全頂点を2^k個に増やすため，最悪計算量はO(Q*(N*2^k+M*2^k)*log2(N*2^k+M*2^k))>10^9 となり，間に合わない．
そこで，N<=400よりまずワーシャルフロイド法で全点対最短経路を求めておく．
指定された橋を全て通る必要があるが，これは橋の通る順番と向きが固定された場合，通り方は1通りとなり，O(K)で求めることができる．
従って，通る順番全てを順列で列挙し，向きも全列挙し，最小コストを求めればよい．
最悪計算量はO(Q*K*K!*2^(K))<10^7 となり，高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef struct bridge{
    int u,v,t;
    bridge(int uu=0,int vv=0,int tt=0):u(uu),v(vv),t(tt){}
}Bridge;

int n,m,q;
vector<Bridge> bridge;
vector<vector<ll> > dp;

const ll INF=(ll)(1e12);

ll solve(vector<int>& tmp){
    int i,bit=0,now;
    ll sum,mmin=INF;
    rep(bit,1<<(int)tmp.size()){
        sum=0;
        now=0;
        rep(i,tmp.size()){
            if(bit&(1<<i)){
                sum+=dp[now][bridge[tmp[i]].u]+bridge[tmp[i]].t;
                now=bridge[tmp[i]].v;
            }else{
                sum+=dp[now][bridge[tmp[i]].v]+bridge[tmp[i]].t;
                now=bridge[tmp[i]].u;
            }
        }
        sum+=dp[now][n-1];
        if(mmin>sum)
            mmin=sum;
    }
    return mmin;
}

int main(){
    int i,j,k;
    ll ans,temp;
    scanf("%d%d",&n,&m);
    dp=vector<vector<ll> >(n,vector<ll>(n,INF));
    while(m--){
        scanf("%d%d%d",&i,&j,&k);
        i--;j--;
        if(k<dp[i][j])dp[i][j]=k;
        if(k<dp[j][i])dp[j][i]=k;
        bridge.push_back(Bridge(i,j,k));
    }
    rep(i,n)dp[i][i]=0;
    rep(i,n)rep(j,n)rep(k,n)if(dp[j][i]+dp[i][k]<dp[j][k])dp[j][k]=dp[j][i]+dp[i][k];
    //rep(i,n){rep(j,n-1)printf("%lld ",dp[i][j]);printf("%lld\n",dp[i][j]);}
    scanf("%d",&q);
    vector<int> tmp;
    while(q--){
        scanf("%d",&k);
        tmp=vector<int>(k);
        rep(i,k){scanf("%d",&tmp[i]);tmp[i]--;}
        ans=INF;
        sort(tmp.begin(),tmp.end());
        do{
            if((temp=solve(tmp))<ans)
                ans=temp;
        }while(next_permutation(tmp.begin(),tmp.end()));
        printf("%lld\n",ans);
    }
    return 0;
}