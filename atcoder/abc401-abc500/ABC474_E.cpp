/*アルゴリズムと工夫点(One Time Coupon/CPU: 45 ms Memory: 5756 KB  Length: 1126 B)
クーポンを消費して購入する商品の数で全探索して解く．
クーポンを使って購入した商品数を固定した時，A - B の差分値の大きいものから優先的に選択していく．
1テストケース当たりの最悪計算量は，O(N * log2(N)) < 10 ^ 7 となり高速．
※ ある商品をA円ではなく，B円で買う -> A - B の差分値で管理すると楽
※ 「各商品が1回しか買えない場合」という簡単な問題設定から考察していくのがコツ
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define MAX_A (int)(1e9)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Good{
    int a, b;

    Good(int a = 0, int b = 0):a(a), b(b){}

    bool operator<(const Good& k)const{
        return this -> a - this -> b < k.a - k.b;
    }
};

int t;

ll solve(){
    int i, j, n;
    scanf("%d", &n);

    ll sum = 0;
    int min_a = MAX_A;
    priority_queue<Good> pq;
    rep(i, n){
        int a, b;
        scanf("%d%d", &a, &b);
        pq.push(Good(a, b));

        sum += a;
        min_a = min(min_a, a);
    }

    ll ans = sum;
    int coupon_cnt = n;
    while(pq.size()){
        auto good = pq.top();pq.pop();

        while(coupon_cnt < 2){
            sum += min_a;
            coupon_cnt++;
        }
        coupon_cnt -= 2;
        sum -= good.a - good.b;

        ans = min(ans, sum);
    }

    return ans;
}

int main(){
    scanf("%d", &t);
    while(t--)printf("%lld\n", solve());
    return 0;
}