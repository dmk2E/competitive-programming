/*アルゴリズムと工夫点(Stone XOR/CPU: 376 ms Memory: 69128 KB  Length: 896 B)
N個のものをいくつかのグループに分割する数はベル数といい，N=12で10^6未満の数となるから，全探索できる．
ベル数を重複なく数え上げるには，要素を順番に訪問し，
・既に存在するグループのいずれかに入る
・新しくグループを作る
のどれかを選択する再帰関数で実装すればよい．
また，種類数を数え上げる時は，座標圧縮と同様の処理を行えばよい．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<ll> a(n),grp,v;
    rep(i,n)scanf("%lld",&a[i]);
    auto rec=[&](auto& f,int now){
        int i;
        if(now==n){
            ll sum=0;
            rep(i,grp.size())sum^=grp[i];
            v.push_back(sum);
            return ;
        }
        rep(i,grp.size()){
            grp[i]+=a[now];
            f(f,now+1);
            grp[i]-=a[now];
        }
        grp.push_back(a[now]);
        f(f,now+1);
        grp.pop_back();
        return ;
    };
    rec(rec,0);
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    printf("%d\n",(int)v.size());
    return 0;
}