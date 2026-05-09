/*アルゴリズムと工夫点(Shift String/CPU: 58 ms Memory: 7548 KB  Length: 944 B)
ローリングハッシュで解く．
最悪計算量は，O(T * |A|) < 10^7 となり高速．
※ 文字列検索のアルゴリズムとして，他にも下記のアルゴリズムが有効．
※ Z-Algorithm : S[0:x) == S[i:i + x) となるxの値を，各iについて O(N) で求められる
*/
#include<iostream>
#include<random>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;
const ll P = 1000000007;

int solve(){
    string a,b;
    cin >> a >> b;
    mt19937_64 mt_for_random;
    ll x = mt_for_random() % P, largest_x = 1, b_hash = 0, a_hash = 0;
    int i;
    rep(i,a.size()){
        a_hash = (a_hash * x) % P;
        a_hash = (a_hash + a[i] - '0') % P;
        b_hash = (b_hash * x) % P;
        b_hash = (b_hash + b[i] - '0') % P;
        largest_x = (largest_x * x) % P;
    }
    rep(i,a.size()){
        if(a_hash == b_hash)return i;
        a_hash = (a_hash * x) % P;
        a_hash = (P + a_hash - (largest_x * (a[i] - '0')) % P) % P;
        a_hash = (a_hash + (a[i] - '0')) % P;
    }
    return -1;
}

int main(){
    scanf("%d",&t);
    while(t--)printf("%d\n",solve());
    return 0;
}