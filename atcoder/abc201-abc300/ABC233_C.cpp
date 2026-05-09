/*アルゴリズムと工夫点(Product/CPU: 5 ms Memory: 3916 KB  Length: 653 B)
(袋に入っているボールの個数の総積)=(ボールの選び方の総数)<10^5 となることから，全探索を行える．
各袋からどのボールを選ぶかを再帰を用いて全探索すればよい．
Li=2の時，N≒log2(10^5) よりN<=16 となるから，最悪計算量は 10^(5)*16<10^7 となり十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
ll x;

int main(){
    int i,j;
    scanf("%d%lld",&n,&x);
    vector<vector<int> > a(n);
    rep(i,n){
        scanf("%d",&j);
        a[i]=vector<int>(j,0);
        rep(j,a[i].size())scanf("%d",&a[i][j]);
    }
    auto rec=[&](auto &f,int now,ll sum)->int{
        if(now==n)return sum==x;
        int i,cnt=0;
        rep(i,a[now].size())if(sum*a[now][i]<=x)cnt+=f(f,now+1,sum*a[now][i]);
        return cnt;
    };
    printf("%d\n",rec(rec,0,1));
    return 0;
}