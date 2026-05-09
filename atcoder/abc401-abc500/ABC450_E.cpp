/*アルゴリズムと工夫点(Fibonacci String/CPU: 81 ms Memory: 5732 KB  Length: 2731 B)
再帰を用いて解く．
フィボナッチ数列の性質より，Siは長さが大体倍になっていくため，S_{100} 程で，10 ^ 18 以上の長さになる．
また，S_{i} = S_{i - 1} + S_{i - 2} という形であるから，S_{i} のZ文字目までの特定のアルファベットの個数についても，
前計算でS_{i}の長さや各アルファベットの数が分かっていれば，再帰的に計算することができる．
従って，1文字目からR文字目まで，文字Cがいくつ含まれるか計算する関数fを用意し，区間和を求める形で解く．
最悪計算量は，O(|X| + |Y| + (Q + 26) * log2(10 ^ 18)) < 10 ^ 7 となり高速．
※ 元々あるデータを何度か合成した後のデータについての走査は，再帰を使えないか考えてみる
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define MAX_LEN (ll)(1e18)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string x, y;
int q;

int main(){
    int i, j;
    const int ALFA = 26;
    cin >> x >> y;

    // X, Y についてアルファベットごとの累積和を求める
    vector<vector<int> > x_alfa_sum(ALFA, vector<int>(x.size() + 1, 0));
    rep(i, ALFA){
        rep(j, x.size())x_alfa_sum[i][j + 1] = x_alfa_sum[i][j] + (x[j] == i + 'a');
    }
    vector<vector<int> > y_alfa_sum(ALFA, vector<int>(y.size() + 1, 0));
    rep(i, ALFA){
        rep(j, y.size())y_alfa_sum[i][j + 1] = y_alfa_sum[i][j] + (y[j] == i + 'a');
    }

    // 文字列毎にアルファベットごとの個数を求める
    vector<vector<ll> > alfaCnt(2, vector<ll>(ALFA, 0));
    for(char c : x)alfaCnt[0][c - 'a']++;
    for(char c : y)alfaCnt[1][c - 'a']++;

    // Si の長さ・alfaCnt を順次求める
    vector<ll> strLen = vector<ll>{(ll)x.size(), (ll)y.size()};
    while(strLen.back() < MAX_LEN){
        int last = strLen.size() - 1;
        strLen.push_back(strLen[last] + strLen[last - 1]);
        alfaCnt.push_back(alfaCnt.back());
        rep(i, ALFA)alfaCnt.back()[i] += alfaCnt[last - 1][i];
    }
    
    // 各クエリに対する解を求める
    auto rec = [&](auto& func, ll last, int c_i, int now) -> ll{
        // printf("%lld %d\n", last, now);
        if(now == 0)return x_alfa_sum[c_i][last + 1];
        if(now == 1)return y_alfa_sum[c_i][last + 1];
        strLen[now - 1] + strLen[now - 2];
        if(last < strLen[now - 1]){
            return func(
                /* func = */ func, 
                /* last = */ last, 
                /* c_i = */ c_i, 
                /* now = */ now - 1
            );
        }
        return alfaCnt[now - 1][c_i] + func(
                /* func = */ func, 
                /* last = */ last - strLen[now - 1], 
                /* c_i = */ c_i, 
                /* now = */ now - 2
        );
    };
    scanf("%d", &q);
    while(q--){
        ll l, r;
        char c;
        scanf("%lld%lld", &l, &r);getchar();
        l--;r--;
        c = getchar();
        ll ans = 
            rec(
                /* func = */ rec, 
                /* last */ r, 
                /* c = */ c - 'a', 
                /* now = */ strLen.size() - 1
            ) - rec(
                /* func = */ rec, 
                /* last */ l - 1, 
                /* c = */ c - 'a', 
                /* now = */ strLen.size() - 1
            );
        printf("%lld\n", ans);
    }
    return 0;
}