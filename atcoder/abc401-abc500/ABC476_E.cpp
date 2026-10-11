/*アルゴリズムと工夫点(Min-Max Swap/CPU: 166 ms Memory: 8476 KB  Length: 4279 B)
セグ木を用いて解く．
区間毎の最小値・最大値を求めるセグ木をそれぞれ用意して，シミュレーションを行えばよい．
最悪計算量は，O(N + M * log2(N)) < 10 ^ 7 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define MAX_P 200000
#define MIN_P 1
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

template<class T, auto op, auto e>
class SegTree{
    int count, size, offset;
    vector<T> tree;

    T queryInternal(int begin, int end, int node_id, int now_begin, int now_end){
        if(now_end <= begin || end <= now_begin)return e;
        if(begin <= now_begin && now_end <= end)return this -> tree[node_id];

        return op(
            this -> queryInternal(
                /* begin = */ begin, 
                /* end = */ end, 
                /* node_id = */ 2 * node_id + 1, 
                /* now_begin = */ now_begin, 
                /* now_end = */ (now_begin + now_end) / 2
            ), this -> queryInternal(
                /* begin = */ begin, 
                /* end = */ end, 
                /* node_id = */ 2 * node_id + 2, 
                /* now_begin = */ (now_begin + now_end) / 2, 
                /* now_end = */ now_end
            )
        );
    }
public:
    SegTree(int count){
        this -> count = count;

        this -> size = 1;
        while(this -> size < count)this -> size *= 2;
        tree = vector<T>(2 * (this -> size) - 1, e);
        offset = this -> size - 1;
    }

    T operator[](int id) const{
        return this -> tree[offset + id];
    }

    void show() const{
        int i;
        for(i = 0; i < this -> size - 1 ; i++)cout << this -> tree[i + this -> offset] << ' ';
        cout << this -> tree[i + this -> offset] << '\n';
    }

    T query(int begin, int end){
        return this -> queryInternal(
            /* begin = */ begin, 
            /* end = */ end, 
            /* node_id = */ 0, 
            /* now_begin = */ 0, 
            /* now_end */ this -> size
        );
    }

    void operate(int id, T x){
        int node_id = id + this -> offset;
        this -> tree[node_id] = op(this -> tree[node_id], x);
        
        while(node_id > 0){
            node_id = (node_id - 1) / 2;
            this -> tree[node_id] = op(
                this -> tree[2 * node_id + 1], 
                this -> tree[2 * node_id + 2]
            );
        }
    }

    void change(int id, T x){
        int node_id = id + this -> offset;
        this -> tree[node_id] = x;
        
        while(node_id > 0){
            node_id = (node_id - 1) / 2;
            this -> tree[node_id] = op(
                this -> tree[2 * node_id + 1], 
                this -> tree[2 * node_id + 2]
            );
        }
    }
};

int n, m;

int opMin(int a, int b){
    return min(a, b);
}

int opMax(int a, int b){
    return max(a, b);
}

int main(){
    int i, j;
    scanf("%d%d", &n, &m);
    vector<int> val_to_id(n);
    rep(i, n){
        int p;
        scanf("%d", &p);
        val_to_id[p - 1] = i;
    }

    SegTree<int, opMin, MAX_P> min_range_tree(/* count = */ n);
    SegTree<int, opMax, MIN_P - 2> max_range_tree(/* count = */ n);
    rep(i, n){
        min_range_tree.operate(/* id = */ val_to_id[i], /* x = */ i);
        max_range_tree.operate(/* id = */ val_to_id[i], /* x = */ i);
    }

    while(m--){
        int l, r;
        scanf("%d%d", &l, &r);
        l--;r--;

        int min_p = min_range_tree.query(
            /* begin = */ l, 
            /* end = */ r + 1
        );
        int max_p = max_range_tree.query(
            /* begin = */ l, 
            /* end = */ r + 1
        );

        min_range_tree.change(
            /* id = */ val_to_id[min_p], 
            /* x = */ max_p
        );
        min_range_tree.change(
            /* id = */ val_to_id[max_p], 
            /* x = */ min_p
        );
        max_range_tree.change(
            /* id = */ val_to_id[min_p], 
            /* x = */ max_p
        );
        max_range_tree.change(
            /* id = */ val_to_id[max_p], 
            /* x = */ min_p
        );
        swap(val_to_id[min_p], val_to_id[max_p]);
    }

    rep(i, n - 1)printf("%d ", min_range_tree[i] + 1);
    printf("%d\n", min_range_tree[i] + 1);
    return 0;
}