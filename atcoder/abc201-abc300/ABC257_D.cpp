/*アルゴリズムと工夫点(Jumping Takahashi 2/CPU: 301 ms Memory: 3936 KB  Length: 1264 B)
ジャンプ力Sの時に，始点を固定してBFSを行い，N個の全頂点を連結にすることが可能であるならば，そのジャンプ力で条件を満たす．
従って，Sについて二分探索を行う．
最悪計算量は O(N^(3)*log2(max(S)))<10^8 となり間に合う．
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> x(n),y(n),p(n);
    rep(i,n)scanf("%d%d%d",&x[i],&y[i],&p[i]);
    const ll MAX_S=(ll)(1e12);
    ll left=0,right=MAX_S,mid;
    auto bfs=[&](int now,const ll& s)->bool{
        int i,c=0;
        vector<bool> vis(n,false);
        queue<int> que;
        que.push(now);
        vis[now]=true;
        c++;
        while(que.size()){
            now=que.front();que.pop();
            rep(i,n){
                if(i==now||vis[i])continue;
                if(s>=((ll)abs(x[now]-x[i])+(ll)abs(y[now]-y[i])+p[now]-1)/p[now]){
                    que.push(i);
                    vis[i]=true;
                    c++;
                }
            }
        }
        return c==n;
    };
    auto judge=[&](ll s)->bool{
        int i;
        rep(i,n)if(bfs(i,s))return true;
        return false;
    };
    while(left<right){
        mid=(left+right)/2;
        if(judge(mid))right=mid;
        else left=mid+1;
    }
    printf("%lld\n",left);
    return 0;
}