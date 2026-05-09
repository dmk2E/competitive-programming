/*アルゴリズムと工夫点(Strange Mirroring/CPU: 96 ms Memory: 4108 KB  Length: 911 B)
文字列の最小単位とし，これを葉とみた時の完全二分木としてみてみると，
・同じ深さの隣り合う頂点の文字列は互いの大文字小文字を反転させたもの
・根から葉までの移動において，左側へ移動すると大小文字の状態は変化せず，右側へ移動すると状態は反転する．
という「再帰的構造」を発見する問題．
これを利用すると，k文字目は元の文字のどの文字かは0-indexedで考えた時，k%|s|番目となる．
問題はこれが大文字か小文字かとなる．まず，k番目の葉が含まれる2^(x)の集合の根まで移動する(左側移動しかしない)．
その後，順番に降りていき，葉に到達するまでの右側移動の回数を求める．これは再帰関数で実装できる．
最悪計算量はO(|S|+Q*log2(max(K)))<10^7 となり高速．
※ある文字列を元に新しい文字列を生成していくとき，計算量的に直接生成することが不可能な場合，元の文字列を最小単位として考え，元の文字列と生成後文字列との関係性を考える． 
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;
int q;
ll k;

int rec(ll l,ll r,ll k){
    if(r-l==1)return 0;
    if(l<=k&&k<(l+r)/2)return rec(l,(l+r)/2,k);
    return 1+rec((l+r)/2,r,k);
}

int main(){
    int i,j;
    cin>>s;
    scanf("%d",&q);
    vector<char> ans;
    while(q--){
        scanf("%lld",&k);
        k--;
        i=rec(0,(ll)(1)<<60,k/((int)s.length()));
        i%=2;
        if(i==1){
            if(isupper(s[k%((int)s.length())]))
                ans.push_back(tolower(s[k%((int)s.length())]));
            else
                ans.push_back(toupper(s[k%((int)s.length())]));
        }else
            ans.push_back(s[k%((int)s.length())]);
    }
    rep(i,ans.size()-1)printf("%c ",ans[i]);
    printf("%c\n",ans[i]);
    return 0;
}