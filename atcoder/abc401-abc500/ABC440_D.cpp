/*アルゴリズムと工夫点(Forbidden List 2/CPU: 169 ms Memory: 7236 KB  Length: 2610 B)
座標圧縮 + 差分の累積和 で解く．
配列Aに含まれる値を，座標圧縮し，昇順で保持して置く．
こうすることで，各値を起点に，解を求める．
また，各値の差分について累積和を取っておく．
すると各クエリについて，座圧したあとの各値について，「どの値を起点とした時の何番目の値か」を二分探索により高速に求めることが出来る．
最悪計算量は，O(N * log2(N) + Q * log2(N)) < 10 ^ 8 となり間に合う．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

template<typename T>
class CC{
    bool initiated;
    vector<T> xs;
public:
    /// @brief 座標圧縮（CoordinatedCompression）のクラス
    CC(){
        xs=vector<T>(0);
        initiated = false;
    }
private:
    void init(){
        initiated=true;
        sort(xs.begin(),xs.end());
        xs.erase(unique(xs.begin(),xs.end()),xs.end());
    }
public:
    int operator()(T k){
        if(!initiated)init();
        return lower_bound(xs.begin(),xs.end(),k)-xs.begin();
    }

    T operator[](int id){
        if(!initiated)init();
        return xs[id];
    }

    /// @brief 要素を追加する関数
    /// @param x 追加する座標
    void add(T x){
        initiated = false;
        xs.push_back(x);
    }

    /// @brief 特定の要素が存在するか判定する関数
    /// @param x 対象要素
    /// @return 判定結果
    bool exist(T x){
        int x_id = (*this)(x);
        return x_id < xs.size() && xs[x_id] == x;
    }

    /// @brief 座標圧縮後の座標総数を返す
    /// @return 座圧後の座標総数
    int size(){
        if(!initiated)init();
        return xs.size();
    }
};

int n, q;

int main(){
    int i, j;
    scanf("%d%d", &n, &q);
    CC<int> as;
    rep(i, n){
        int a;
        scanf("%d", &a);
        as.add(a);
    }
    // diff[i] := as[i + 1] - as[i]
    vector<int> diff(as.size() - 1), sum_diff(as.size(), 0);
    rep(i, as.size() - 1){
        diff[i] = as[i + 1] - as[i] - 1;
        sum_diff[i + 1] = sum_diff[i] + diff[i];
    }
    while(q--){
        int x, y;
        scanf("%d%d", &x, &y);
        int x_id = as(x);
        if(x_id == as.size()){
            printf("%d\n", x + y - 1);
            continue;
        }
        if(!as.exist(x)){
            x_id--;
            if(as[x_id + 1] - x >= y){
                printf("%d\n", x + y - 1);
                continue;
            }
            y -= as[x_id + 1] - x;
            x_id++;
        }
        int start_id = lower_bound(sum_diff.begin(), sum_diff.end(), y + sum_diff[x_id]) - sum_diff.begin() - 1;
        printf("%d\n", start_id < as.size() ? 
                       as[start_id] + y - (sum_diff[start_id] - sum_diff[x_id]) : 
                       as[as.size() - 1] + y - (sum_diff[as.size() - 1] - sum_diff[x_id])
        );
    }
    return 0;
}