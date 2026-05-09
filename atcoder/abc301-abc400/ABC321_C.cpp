/*アルゴリズムと工夫点(321-like Searcher/CPU: 1 ms Memory: 3920 KB  Length: 1051 B)
再帰全探索で解く．
桁数Dの 321-like Number の総数は，各桁がとり得る数の種類には制限があり，
多く見積もっても，Σ(D ∈ [1, 10]) (11 - D) ^ D < 10 ^ 5 より全列挙が可能．
再帰で列挙を行うが，探索の順番を工夫することで降順列挙が可能であり，また枝刈りにより高速化している．
最悪計算量は，10 ^ 5 未満となり十分高速．
※ 本実装では，0 も 321-like Number として列挙していることに注意
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int k;

int main(){
    int i;
    scanf("%d", &k);
    
    vector<ll> nums;
    auto rec = [&](auto& func, int rest_digit, int prev, ll num) -> void{
        if(rest_digit == 0){
            nums.push_back(num);
            return ;
        }
        int i;
        for(i = prev - 1;i >= 0;i--){
            // 先頭が i から始まる 321-like Number で，最大の桁数は i + 1
            if(i + 1 < rest_digit)break;
            func(
                /* func = */ func, 
                /* rest_digit = */ rest_digit - 1, 
                /* prev = */ i, 
                /* num = */ num * 10 + i
            );
        }
    };
    const int MAX_DIGIT = 10;
    for(i = MAX_DIGIT;i > 0;i--){
        rec(
            /* func = */ rec, 
            /* rest_digit = */ i, 
            /* prev = */ 10, 
            /* num = */ 0
        );
    }

    printf("%lld\n", nums[nums.size() - 1 - k]);
    return 0;
}