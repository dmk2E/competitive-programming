/*アルゴリズムと工夫点(Integers on Grid/CPU: 1247 ms Memory: 57104 KB  Length: 897 B)
dp[i]:コマが(ri,ci)に置かれている時，それ以降にコマの移動を行うことができる回数の最大値
として，aの降順にdp[i]の値を求めていく．
※座標圧縮して，メモ化再帰で間に合うかと思ったが，TLE&RE...
*/
#include<iostream>
#include<vector>
#include<map>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> p;

int h,w,n,r,c,a;

void chmax(int& x,int y){x=max(x,y);}

int main(){
    int i,j;
    scanf("%d%d%d",&h,&w,&n);
    map<int,vector<p> > mp;
    map<p,int> cell;
    rep(i,n){
        scanf("%d%d%d",&r,&c,&a);
        mp[-a].push_back(p(r,c));
        cell[p(r,c)]=i;
    }
    vector<int> ans(n);
    map<int,int> maxY,maxX;
    for (auto [_,ps]:mp){
        for(auto [r,c]:ps){
            int now=max(maxY[r],maxX[c]);
            ans[cell[p(r,c)]]=now;
        }
        for(auto [r,c]:ps){
            int now=ans[cell[p(r,c)]];
            chmax(maxY[r],now+1);
            chmax(maxX[c],now+1);
        }
    }
    rep(i,n)printf("%d\n",ans[i]);
    return 0;
}