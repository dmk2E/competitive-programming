/*アルゴリズムと工夫点(Team Division/CPU: 29 ms Memory: 8472 KB  Length: 2209 B)
逆元 + imos法で解く．
2チームそれぞれの人数 x, N - x を固定した時のチーム分けとしてあり得る振り分けの個数を求めることを考える．
この時，片方だけにしか属せない人数と，両方とも属せる人数が分かれば，nCr の計算を利用して高速に計算可能．
この時，人数xにチームに属せるか否かは単純なimos法で求められる．
人数がそれぞれx, N - x チームそれぞれに属することができるかは下記の手法で求められる．
 人数がx, N - x の両方のチームに属するとは，下記の条件式を満たすことと同義
 * L <= x <= R - <i>
 * L <= N - x <= R - <ii>
 <ii> を言い換えると，L - N <= -x <= R - N より，N - R <= x <= N - L
 これと <i> との共通範囲を考えると，
 max(L, N - R) <= x <= min(R, N - L)
 従ってこの範囲のみ加算した別の配列を imos 法で求めればよい．
最悪計算量は，O(N) < 10 ^ 6 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

class Combination{
    int mod, max_num;
    vector<ll> fact, inv_fact;

    ll power(ll num, ll pow){
        ll val = 1, pow_num = num;
        while(pow > 0){
            if(pow & 1)val = (val * pow_num) % this -> mod;
            pow_num = (pow_num * pow_num) % this -> mod;
            pow >>= 1;
        }
        return val;
    }

public:
    Combination(int max_num, int mod = 998244353): max_num(max_num), mod(mod){
        int i;
        fact = vector<ll>(this -> max_num + 1);fact[0] = 1;
        rep(i, this -> max_num){
            fact[i + 1] = (fact[i] * (i + 1)) % this -> mod;
        }

        inv_fact = vector<ll>(this -> max_num + 1);
        inv_fact[this -> max_num] = this -> power(
            /* num = */ fact[this -> max_num], 
            /* pow = */ this -> mod - 2
        );
        for(i = this -> max_num - 1;i >= 0;i--)inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % this -> mod;
    }

    ll comb(int n, int r){
        assert(n >= r);
        return (((this -> fact[n] * this -> inv_fact[n - r]) % this -> mod) * this -> inv_fact[r]) % this -> mod;
    }
};

int n;

int main(){
    int i;
    scanf("%d", &n);
    vector<int> imos(n + 2, 0), imos2(n + 2, 0);
    rep(i, n){
        int l, r;
        scanf("%d%d", &l, &r);
        imos[l]++;imos[r + 1]--;
        l = max(l, n - r);
        r = min(r, n - l);
        if(l <= r){
            imos2[l]++;imos2[r + 1]--;
        }
    }
    rep(i, n + 1){
        imos[i + 1] += imos[i];
        imos2[i + 1] += imos2[i];
    }

    ll ans = 0;
    Combination comb(/* max_num = */ n, /* mod = */ MOD);
    rep(i, n - 1){
        int x = i + 1, y = n - (i + 1);
        int a = imos[x], b = imos[y], c = imos2[x];
        a -= c;b -= c;
        if(a + b + c != n || a > x || b > y)continue;
        ans = (ans + comb.comb(
            /* n = */ c, 
            /* r = */ x - a
            )) % MOD;
    }
    printf("%lld\n", ans);
    return 0;
}