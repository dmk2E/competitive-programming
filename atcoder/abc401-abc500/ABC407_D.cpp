/*アルゴリズムと工夫点(Domino Covering XOR/CPU: 3 ms Memory: 3960 KB  Length: 1299 B)
盤面が小さいため，有り得る置き方を全探索する．
実装は再帰を用いるのが楽（構造的にはDFS）．
最悪計算量は O((H*W)^(2)*3^(H)*3^(W))=7873200<10^7 となり高速．
※計算量の見積り手法：
f(N)=(Nマス残っている状態からのあり得るパターン数)
とすると，何も置かないことを決めると，そのマスには何も置かれないため，
f(N)=2*f(N-2)+f(N-1), f(0)=f(1)=1 という漸化式が求まる．
f(20)=699051<10^6 となり，20*f(20)<10^7 となり高速．
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
    int now,last=1,pre_last=1;
    i=1;
    while(i<20){
        now=last+2*pre_last;
        pre_last=last;
        last=now;
        i++;
    }
    printf("%d\n",last);
    return 0;
    ll ans=0,sum=0;
    scanf("%d%d",&h,&w);
    vector<vector<ll> > a(h,vector<ll>(w));
    vector<vector<bool> > flag(h,vector<bool>(w,false));
    rep(i,h)rep(j,w){
        scanf("%lld",&a[i][j]);
        sum^=a[i][j];
    }
    auto rec=[&](auto& func,int now,ll sum)->void{
        if(now==h*w){
            ans=max(ans,sum);
            return ;
        }
        int y=now/w,x=now%w;
        if(flag[y][x])func(func,now+1,sum);
        else{
            // yoko
            if(x+1<w&&flag[y][x+1]==false){
                flag[y][x]=flag[y][x+1]=true;
                func(func,now+1,sum^(a[y][x])^(a[y][x+1]));
                flag[y][x]=flag[y][x+1]=false;
            }
            // tate
            if(y+1<h&&flag[y+1][x]==false){
                flag[y][x]=flag[y+1][x]=true;
                func(func,now+1,sum^(a[y][x])^(a[y+1][x]));
                flag[y][x]=flag[y+1][x]=false;
            }
            // nothing
            func(func,now+1,sum);
        }
    };
    rec(rec,0,sum);
    printf("%lld\n",ans);
    return 0;
}