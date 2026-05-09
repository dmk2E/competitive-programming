/*アルゴリズムと工夫点(Clouds/CPU: 128 ms Memory: 38192 KB  Length: 1362 B)
二次元imos法 + 二次元累積和 で解く．
取り除かれる雲の数は1つであるから，1つの雲でのみ覆われているマス one_cover に着目する．
また，雲を取り除く前の時点で，どの雲でも覆われていないマスの個数 sum_free を別で求めておく．
すると sum_free に，取り除く雲の範囲に存在する，その雲にのみ覆われているマスの数を加算すれば解が求まる．
one_cover は二次元imos法を用いて求めることができ，二次元累積和の形で区間内の1つの雲でのみ覆われているマスの数を別で保持することで，解を高速に求められる．
最悪計算量は，O(N + MAX_H * MAX_W) < 10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_H 2000
#define MAX_W 2000
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> u(n), d(n), l(n), r(n);
    vector<vector<int> > imos(MAX_H + 1, vector<int>(MAX_W + 1, 0)), sum_one_cover(MAX_H + 1, vector<int>(MAX_W + 1, 0));
    auto f = [&](int sy, int sx, int gy, int gx) -> int{
        // [sy, gy] [sx, gx]
        return sum_one_cover[gy + 1][gx + 1] - sum_one_cover[gy + 1][sx] - sum_one_cover[sy][gx + 1] + sum_one_cover[sy][sx];
    };
    rep(i, n){
        scanf("%d%d%d%d", &u[i], &d[i], &l[i], &r[i]);
        u[i]--;d[i]--;l[i]--;r[i]--;
        imos[u[i]][l[i]]++;
        imos[u[i]][r[i] + 1]--;
        imos[d[i] + 1][l[i]]--;
        imos[d[i] + 1][r[i] + 1]++;
    }
    int sum_free = 0;
    rep(i, MAX_H + 1)rep(j, MAX_W)imos[i][j + 1] += imos[i][j];
    rep(j, MAX_W + 1)rep(i, MAX_H)imos[i + 1][j] += imos[i][j];
    rep(i, MAX_H)rep(j, MAX_W){
        sum_one_cover[i + 1][j + 1] = (imos[i][j] == 1) + sum_one_cover[i][j + 1] + sum_one_cover[i + 1][j] - sum_one_cover[i][j];
        if(imos[i][j] == 0)sum_free++;
    }
    rep(i, n)printf("%d\n", sum_free + f(u[i], l[i], d[i], r[i]));
    return 0;
}