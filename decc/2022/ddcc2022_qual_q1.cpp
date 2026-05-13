/*アルゴリズムと工夫点(あまりにも暇だったので素数を足してみた。/CPU: - ms Memory: - KB  Length: - B)
エラトステネスの篩を用いて解く．
与えられる値Xとすると，[1, X] の範囲で素数であるものを列挙し，その素数群で条件を満たすものを全探索すればよい．
最悪計算量は，O(X * log2(log2(X))) < 10 ^ 5 となり，十分高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define INPUT_NUMBER 3
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

template<typename T>
class Outputer{
    vector<T> ans;

public:
    Outputer(){}

    void push(T value){
        ans.push_back(value);
    }

    void output(){
        int i;
        if(ans.size() > 0){
            rep(i, ans.size() - 1)cout << ans[i] << ',';
            cout << ans[i] << '\n';
        }
    }
};

typedef class PrimeMaster{
    const int NIL = -1;
    vector<int> min_fact;

public:
    vector<bool> is_prime;

    /// @brief 素数関係の処理をまとめたクラス
    /// @param max_val 扱う最大の正整数値（初期化処理：O(max_val * log2(max_val))）
    PrimeMaster(int max_val){
        min_fact = vector<int>(max_val + 1, NIL);
        min_fact[0] = min_fact[1] = 1;

        // エラトステネスの篩で対象範囲内の整数について素数判定
        is_prime = vector<bool>(max_val + 1, true);
        is_prime[0] = is_prime[1] = false;
        for(int i = 2;i <= max_val;i++){
            if(is_prime[i]){
                min_fact[i] = i;
                int j = 2 * i;
                while(j <= max_val){
                    is_prime[j] = false;
                    min_fact[j] = i;
                    j += i;
                }
            }
        }
    }

    /// @brief 素朴な素数判定法（O(√N)）
    /// @param x 対象の正整数
    /// @return bool値: 素数か否か
    bool isPrime(int x){
        if(x == 2)return true;
        if(x <= 1 || x % 2 == 0)return false;
        for(int i = 3;i <= x / i;i += 2)if(x % i == 0)return false;
        return true;
    }

    /// @brief 高速な素因数分解を行う（O(log2(X))）
    /// @param x [0, max_val] 内の整数値
    /// @return vector<pair<int, int> >: 素因数分解の結果
    vector<pair<int, int> > convertToPFs(int x){
        vector<pair<int, int> > ans;
        while(x > 1){
            int divider = min_fact[x];
            ans.push_back(pair<int, int>(divider, 0));
            while(x % divider == 0){
                x /= divider;
                ans.back().second++;
            }
        }
        return ans;
    }
}PM;

// vector<int> ipt = {
//     24,
//     5432,
//     2454
// };
vector<int> ipt = {
    9876,
    1358,
    4922
};
Outputer<int> answer;

int main(){
    int i, j;

    for(int ipt_id = 0;ipt_id < INPUT_NUMBER;ipt_id++){
        auto& val = ipt[ipt_id];

        vector<int> primes;
        auto is_prime = PM(/* max_val = */ val).is_prime;
        rep(i, val + 1)if(is_prime[i])primes.push_back(i);
        
        int ans = 0;
        rep(i, primes.size())rep(j, i + 1)if(primes[i] + primes[j] == val)ans = max(ans, primes[i] * primes[j]);
        answer.push(ans);
    }

    answer.output();
    return 0;
}