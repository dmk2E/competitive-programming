/*アルゴリズムと工夫点(Unbalanced ABC Substrings/CPU: 58 ms Memory: 20448 KB  Length: 2523 B)
累積和と包除原理を用いて解く．
下記の3条件を考える．
 ・条件a : A = B
 ・条件b : B = C
 ・条件c : C = A
求めたい個数は，f(not(a) and not(b) and not(c)) = n * (n + 1) / 2 - f(a or b or c) となる．
ここで包除原理より，f(a or b or c) = f(a) + f(b) + f(c) 
                                     - f(a and b) - f(b and c) - f(c and a)
                                     + f(a and b and c)

条件式より，f(a and b) = f(b and c) = f(c and a) = f(a and b and c) となるため，
f(?) と，f(a and b and c) を高速に求められればよい．

・f(?)
 条件 a を式変形すると，A - B = 0 ．従って，「A - B」の値について累積和を取ることを考える．
 すると，区間の左端 l を固定した時，sum_a_minus_b[l] = sum_a_minus_b[r] (l < r) を満たす r の個数を加算していけばよい
・f(a and b and c)
 f(?) とほぼ同様．(A - B, A - C) の組の値で各インデックスにおける累積和を考えればよい．

最悪計算量は，O(N * log2(N)) < 10 ^ 7 となり高速．
*/
#include<iostream>
#include<vector>
#include<map>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int, int> P;

int n;
string s;

ll countSumEqual(vector<int>& sum_arr){
    ll ans = 0;
    vector<int> sum_to_cnt(2 * n + 1, 0);
    for(int l = n;l >= 0;l--){
        int offset_sum = sum_arr[l] + n;
        ans += sum_to_cnt[offset_sum];
        sum_to_cnt[offset_sum]++;
    }

    return ans;
}

ll countSumEqual(vector<P>& sum_arr){
    ll ans = 0;
    map<P, int> sum_to_cnt;
    for(int l = n;l >= 0;l--){
        ans += sum_to_cnt[sum_arr[l]];
        sum_to_cnt[sum_arr[l]]++;
    }

    return ans;
}

int main(){
    int i, j;
    scanf("%d", &n);
    cin >> s;

    vector<int> sum_a_minus_b(1, 0), sum_b_minus_c(1, 0), sum_c_minus_a(1, 0);
    vector<P> sum_ab_ac(1, P(0, 0));
    for(char c : s){
        switch(c){
            case 'A': {
                sum_a_minus_b.push_back(sum_a_minus_b.back() + 1);
                sum_c_minus_a.push_back(sum_c_minus_a.back() - 1);
                sum_b_minus_c.push_back(sum_b_minus_c.back());

                auto [sum_ab, sum_ac] = sum_ab_ac.back();
                sum_ab_ac.push_back(P(sum_ab + 1, sum_ac + 1));
                break;
            }
            case 'B': {
                sum_b_minus_c.push_back(sum_b_minus_c.back() + 1);
                sum_a_minus_b.push_back(sum_a_minus_b.back() - 1);
                sum_c_minus_a.push_back(sum_c_minus_a.back());

                auto [sum_ab, sum_ac] = sum_ab_ac.back();
                sum_ab_ac.push_back(P(sum_ab - 1, sum_ac));
                break;
            }
            case 'C': {
                sum_c_minus_a.push_back(sum_c_minus_a.back() + 1);
                sum_b_minus_c.push_back(sum_b_minus_c.back() - 1);
                sum_a_minus_b.push_back(sum_a_minus_b.back());

                auto [sum_ab, sum_ac] = sum_ab_ac.back();
                sum_ab_ac.push_back(P(sum_ab, sum_ac - 1));
                break;
            }
            default:
                break;
        }
    }

    ll ans = ((ll)n * (n + 1)) / 2;
    ans -= countSumEqual(/* sum_arr = */ sum_a_minus_b);
    ans -= countSumEqual(/* sum_arr = */ sum_b_minus_c);
    ans -= countSumEqual(/* sum_arr = */ sum_c_minus_a);
    ans += 2 * countSumEqual(/* sum_arr = */ sum_ab_ac);

    printf("%lld\n", ans);
    return 0;
}