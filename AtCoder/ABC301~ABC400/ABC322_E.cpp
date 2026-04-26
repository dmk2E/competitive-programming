/*アルゴリズムと工夫点(Product Development/CPU: 151 ms Memory: 4964 KB  Length: 1649 B)
動的計画法で解く．
K個のパラメータの各値の状態として，あり得るパターン数は，K ^ P < 10 ^ 4 となり，少ないため，
 dp[i][j] := ([1, i + 1) 番目までの開発案を実行するか否かを決定した時，パラメータが 状態j となるような，最小のコストの総和)
 ※ 状態j：各パラメータの状態を，「パラメータ値を連結することでできる整数値」として表現したもの
という形のDPを解けばよい．
最悪計算量は，O(N * K ^ (P) * log(K ^ P)) < 10 ^ 7 となり，高速．
*/
#include<iostream>
#include<vector>
#include<map>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n, k, p;

int addParams(int param1, int param2){
    int i;
    vector<int> tmp;
    rep(i, k){
        int added_val = (param1 % 10) + (param2 % 10);
        tmp.push_back(min(p, added_val));
        param1 /= 10;param2 /= 10;
    }

    int added_params = 0;
    rep(i, k){
        added_params *= 10;
        added_params += tmp[k - 1 - i];
    }
    return added_params;
}

int main(){
    int i, j;
    scanf("%d%d%d", &n, &k, &p);

    map<int, ll> params_to_cost;
    params_to_cost[0] = 0;
    while(n--){
        int c, num_a = 0;
        scanf("%d", &c);
        rep(i, k){
            int a;
            scanf("%d", &a);
            num_a *= 10;num_a += a;
        }

        map<int, ll> nxt;
        for(auto [params, cost] : params_to_cost){
            if(nxt.count(params))nxt[params] = min(nxt[params], cost);
            else nxt[params] = cost;

            int added_params = addParams(
                /* param1 = */ params, 
                /* param2 = */ num_a
            );
            if(nxt.count(added_params))nxt[added_params] = min(nxt[added_params], cost + c);
            else nxt[added_params] = cost + c;
        }

        swap(params_to_cost, nxt);
    }

    const int NIL = -1;
    int goal = 0;
    rep(i, k){
        goal *= 10;
        goal += p;
    }
    printf("%lld\n", params_to_cost.count(goal) ? params_to_cost[goal] : NIL);
    return 0;
}