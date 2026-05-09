/*アルゴリズムと工夫点(Don't Isolate Elements/CPU: 53 ms Memory: 7576 KB  Length: 1884 B)
i-1行目まで操作を適切に行い，孤立した要素が存在しないとする．この時，Aのi行目に操作を行った結果，i行目に孤立した要素が存在するかはi-1行目に依存する．
そしてそのi-1行目に孤立した要素が存在しないかはi-2行目に依存する．
従って，「i-1,i-2行目それぞれで操作を行ったか否か」の状態で，i行目時点で行う必要がある最小回数を求める．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define NIL -1
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w;
vector<vector<int> > a;

int main(){
    int i,j,k;
    scanf("%d%d",&h,&w);
    a=vector<vector<int> >(h,vector<int>(w,false));
    rep(i,h)
        rep(j,w){
            scanf("%d",&k);
            a[i][j]=k;
        }
    auto get=[&](int row,int flip)->vector<int>{
        vector<int> tmp=a[row];
        if(flip)rep(j,w)tmp[j]^=1;
        return tmp;
    };
    auto check=[&](const vector<int>& a0,const vector<int>& a1,const vector<int>& a2)->bool{
        rep(j,w){
            if(a0[j]==a1[j])continue;
            if(a2[j]==a1[j])continue;
            if(j-1>=0&&a1[j-1]==a1[j])continue;
            if(j+1<w&&a1[j+1]==a1[j])continue;
            return false;
        }
        return true;
    };
    const int INF=h+1;
    vector<int> dp(1<<2,INF);
    rep(i,1<<2){
        int cnt=0;
        vector<int> a0(w,NIL);
        auto a1=get(0,i&(1<<1));
        auto a2=get(1,i&(1<<0));
        if(i&(1<<1))cnt++;
        if(i&(1<<0))cnt++;
        if(check(a0,a1,a2))dp[i]=cnt;
    }
    int s,x;
    for(i=2;i<h;i++){
        vector<int> tmp(1<<2,INF);
        swap(tmp,dp);
        rep(s,4){
            auto a0=get(i-2,s&(1<<1));
            auto a1=get(i-1,s&(1<<0));
            rep(x,2){
                auto a2=get(i,x);
                if(check(a0,a1,a2)){
                    int ns=((s&1)<<1)|x;
                    dp[ns]=min(dp[ns],tmp[s]+x);
                }
            }
        }
    }
    x=INF;
    rep(s,4){
        auto a0=get(h-2,s&(1<<1));
        auto a1=get(h-1,s&(1<<0));
        vector<int> a2(w,NIL);
        if(check(a0,a1,a2))x=min(x,dp[s]);
    }
    printf("%d\n",x==INF?NIL:x);
    return 0;
}