/*アルゴリズムと工夫点(183184/CPU: 1188 ms Memory: 3904 KB  Length: 1209 B)
二分探索を用いた区間和の高速計算を用いて解く．
f(C, C+x) (1 <= x <= D) において，右半分の値の桁が変化する前後は，f(...)の値は連続値となる．
従って，特定の区間における平方数の数を高速に計算できれば良い．
よって，最悪計算量は，O(T * log2(MAX) * log10(MAX)) < 10^8 となり間に合う．
※ 公式解説は二分探索ではなくsqrtl関数を使っていた
*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;
const int MAX = (2e9);

ll str2Int(string s){
    ll ans = 0;
    for(char x : s){
        ans *= 10;
        ans += ((int)x - (int)'0');
    }
    return ans;
}

ll calNext(ll x){
    ll ans = 1;
    while(x > 0){
        x /= 10;
        ans *= 10;
    }
    return ans;
}

ll count(ll x){
    ll left = 0, right = MAX;
    while(left < right){
        ll mid = (left + right) / 2;
        if(mid <= x / mid)left = mid + 1;
        else right = mid;
    }
    return left - 1;
}

ll solve(){
    string str_c;
    ll c, d, ans = 0, max_x;
    cin >> str_c >> d;
    c = str2Int(str_c);
    max_x = c + d;
    for(ll top = c + 1, tail = min(max_x, calNext(top) - 1);top <= max_x; top = tail + 1, tail = min(max_x, top * 10 - 1)){
        ll start = str2Int(str_c + to_string(top));
        ll end = str2Int(str_c + to_string(tail));
        ans += count(end) - count(start - 1);
    }
    return ans;
}

int main(){
    scanf("%d",&t);
    while(t--)printf("%lld\n",solve());
    return 0;
}