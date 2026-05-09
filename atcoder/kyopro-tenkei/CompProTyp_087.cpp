/*アルゴリズムと工夫点(Chokudai's Demand（★5）/CPU: 266 ms Memory: 3920 KB  Length: 2145 B)
Xの増加に対し，「経路を適切に選んだ時の街iから街jまでの合計Pスヌーク以下で到達可能であるような(i,j)の組の数y」は広義単調減少する．
従って二分探索を行うことができる．
yの値はダイクストラ法を用いることで，O(N^(3)*log2(N))で求められるため，最悪計算量はO(N^(3)*log2(N)*log2(INF))≒10^7 となる．
※全点対最短経路問題を解く「ワーシャルフロイド法」の方が，計算量的には早い．
※Xが正の整数の範囲であることに気づけず，1WA．問題文をよく読むこと!!!
※キーワード:「全点対最短経路はワーシャルフロイド法」「答えで二分探索」
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define NIL -1
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;
typedef pair<ll,int> PP;

int n,p,k;

int main(){
    int i,j;
    scanf("%d%d%d",&n,&p,&k);
    vector<vector<ll> > adj(n,vector<ll>(n));
    vector<P> tmp;
    rep(i,n){
        rep(j,n){
            scanf("%lld",&adj[i][j]);
            if(adj[i][j]==NIL)tmp.push_back(P(i,j));
        }
    }
    const ll INF=(ll)(1e15);
    auto dijk=[&](int s,ll x)->int{
        int i,cnt=0;
        PP now;
        vector<ll> visited(n,INF);
        priority_queue<PP> PQ;
        PQ.push(PP(0,s));
        while(PQ.size()){
            do{
                now=PQ.top();PQ.pop();
            }while(PQ.size()&&visited[now.second]!=INF);
            if(visited[now.second]==INF)visited[now.second]=-now.first;
            else break;
            rep(i,n){
                if(visited[i]==INF)PQ.push(PP(now.first-adj[now.second][i],i));
            }
        }
        for(s++;s<n;s++)if(visited[s]<=p)cnt++;
        return cnt;
    };
    auto count=[&](ll x)->int{
        int i,cnt=0;
        rep(i,tmp.size())adj[tmp[i].first][tmp[i].second]=x;
        rep(i,n)cnt+=dijk(i,x);
        return cnt;
    };
    auto search1=[&](int k)->ll{
        ll left=1,right=INF,mid;
        while(left<right){
            mid=(left+right)/2;
            if(count(mid)>k)
                left=mid+1;
            else
                right=mid;
        }
        //printf("1:%lld\n",left);
        return left;
    };
    auto search2=[&](int k)->ll{
        ll left=1,right=INF,mid;
        while(left<right){
            mid=(left+right)/2;
            if(count(mid)>=k)
                left=mid+1;
            else
                right=mid;
        }
        //printf("2:%lld\n",left);
        return left;
    };
    ll right=search2(k),left=search1(k);
    if(right==INF&&left!=INF)
        puts("Infinity");
    else
        printf("%lld\n",right-left);
    return 0;
}