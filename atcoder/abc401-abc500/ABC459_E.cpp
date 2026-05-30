/*アルゴリズムと工夫点(Select from Subtrees/CPU: 91 ms Memory: 41964 KB  Length: 4146 B)
オイラーツアー（DFS）で解く．
木の葉から順に，リスにアメを選ばせていき，その場合の数を乗算により計算していく．
この時，頂点から頂点への移動の際，選んでいない残りのアメの個数を親の頂点の個数に加算していくする．
こうすることで，その頂点でのアメの選び方の計算の際，その頂点を根とする部分木に含まれるアメの総和を同時に求められる．
また，アメの個数は非常に大きくなることがあるため，組み合わせの計算の際は下記の方法で対応する
 ・forループを用いた順次加算と
 ・階乗の逆元の前計算（選ぶアメの個数の総和の数は 10 ^ 6 以下であるため可能）
最悪計算量は，O(N + Σ D) < 10 ^ 7 となり，高速．
※ 適切な余りの計算ができていなかったため，オーバーフローしてしまい，一発ACできず...
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define MAX_SUM_D (int)(1e6)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

class Combination{
    int mod, max_num;
    vector<ll> fact, inv_fact;

    /// @brief 繰り返し自乗法で高速に累乗を計算する
    /// @param num 被累乗数
    /// @param pow 累乗数
    /// @return num ^ pow を mod で割った余り
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
    /// @brief 組合せ nCr を計算するクラス
    /// @param max_num n の値としてとり得る最大値
    /// @param mod 計算にてとる余りの値
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

    /// @brief 階乗の逆元を取得する
    /// @param num 階乗の値
    /// @return 階乗の逆元を mod で割った余り
    ll getInvFact(int num){
        assert(num < inv_fact.size());
        return this -> inv_fact[num];
    }

    /// @brief N個の中からr個だけ選ぶ組合せの総数を求める
    /// @param n 選択肢の数
    /// @param r 選ぶ数
    /// @return nCr を mod で割った余り
    ll comb(int n, int r){
        assert(n >= r);
        return (((this -> fact[n] * this -> inv_fact[n - r]) % this -> mod) * this -> inv_fact[r]) % this -> mod;
    }

    /// @brief n個の箱に，r個のボールを振り分ける場合の数の総数を求める
    /// @param n 箱の数
    /// @param r ボールの数
    /// @return 総数を mod で割った余り
    ll countDistributions(int n, int r){
        // r個のボールを，n - 1 本の線で区切る方法の総数を求めると考えられるから，
        // n + r - 1 個の選択肢の内，r個だけボールとする場合の数を言い換えられる
        return this -> comb(/* n = */ n + r - 1, r);
    }
};

typedef pair<ll, ll> P; // (数え上げの数, 残りのアメの個数)

int n;

int main(){
    int i, j;
    
    scanf("%d", &n);
    vector<vector<int> > adj(n);
    rep(i, n - 1){
        int p;
        scanf("%d", &p);p--;
        adj[i + 1].push_back(p);
        adj[p].push_back(i + 1);
    }

    vector<int> c(n);
    rep(i, n)scanf("%d", &c[i]);

    vector<int> d(n);
    rep(i, n)scanf("%d", &d[i]);

    Combination comb(/* max_num = */ MAX_SUM_D, /* mod = */ MOD);
    auto dfs = [&](auto& func, int prev, int root) -> P{
        ll ans = 1;
        
        ll num_candy = c[root];
        for(int nxt : adj[root])if(nxt != prev){
            auto [sum, rest_candy] = func(
                /* func = */ func, 
                /* prev = */ root, 
                /* root = */ nxt
            );
            ans = (ans * sum) % MOD;
            num_candy += rest_candy;
        }

        if(num_candy < d[root])return P(0, num_candy - d[root]);
        
        ll sum = 1;
        for(int i = 0;i < d[root];i++, num_candy--)sum = (sum * (num_candy % MOD)) % MOD;
        sum = (sum * comb.getInvFact(/* num = */ d[root])) % MOD;

        return P((ans * sum) % MOD, num_candy);
    };

    const int NIL = -1;
    auto [ans, _] = dfs(
        /* func = */ dfs, 
        /* prev = */ NIL, 
        /* root = */ 0
    );
    printf("%lld\n", ans);
    return 0;
}