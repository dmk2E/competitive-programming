/*アルゴリズムと工夫点(Hungry Takahashi/CPU: 475 ms Memory: 26044 KB  Length: 1245 B)
二分探索+動的計画法で解く．
コインの枚数xについて，十分に足りているか否かについては単調性が存在する．
従ってあるxを決め打った時，一度も空腹で倒れることなくH+W-1日間を終えられるか判定すればよい．
この判定は以下の動的計画法で行う．
dp[i][j]:マスiで，手順1,2まで行ったときの，最大のコイン枚数
dp[H][W]でのコイン枚数が0以上であるならば，条件を満たす．
よって最悪計算量は，O(H*W*log2(max(Aij)*H*W))<10^8 となり間に合う．
※バーチャル参加
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w;

int main(){
    int i,j;
    scanf("%d%d",&h,&w);
    vector<vector<int> > a(h,vector<int>(w,0));
    vector<int> p(h+w-1,0);
    rep(i,h)rep(j,w)scanf("%d",&a[i][j]);
    rep(i,p.size())scanf("%d",&p[i]);
    const ll INF=(ll)(1e15),NIL=-1;
    const int DY[]={0,1},MAX_D=2;
    const int DX[]={1,0};
    ll left=0,right=INF;
    auto judge=[&](ll x)->bool{
        vector<vector<ll> > dp(h,vector<ll>(w,NIL));
        dp[0][0]=x+a[0][0]-p[0];
        if(dp[0][0]<0)return false;
        int i,j,k;
        rep(i,h)rep(j,w){
            rep(k,MAX_D){
                int y=i-DY[k],x=j-DX[k];
                if(0<=y&&y<h
                  &&0<=x&&x<w
                  &&dp[y][x]>=0
                  &&dp[y][x]+a[i][j]-p[i+j]>=0
                )dp[i][j]=max(dp[i][j],dp[y][x]+a[i][j]-p[i+j]);
            }
        }
        return dp[h-1][w-1]>=0;
    };
    while(left<right){
        ll mid=(left+right)/2;
        if(judge(mid))right=mid;
        else left=mid+1;
    }
    printf("%lld\n",left);
    return 0;
}