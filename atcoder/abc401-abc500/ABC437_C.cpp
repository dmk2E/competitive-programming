/*アルゴリズムと工夫点(Reindeer and Sleigh 2/CPU: 53 ms Memory: 5968 KB  Length: 953 B)
貪欲法で解く．
満たすべき条件式 Σ wi <= sum_p - Σ pi より，Σ (wi + pi) <= sum_p を満たせばよい．
従って重さと力の総和の小さい順にソリに乗せていけばよい．
最悪計算量は，O(N * log2(N)) < 10^7 となり高速．
※ 困ったときは条件式に変換して考えてみる．この時，定数を無理やり作り出すなどするとシンプルな条件式になることがある．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int t;

int solve(){
    int i,j,n,ans = 0;
    ll sum_p = 0, sum_left = 0;
    scanf("%d", &n);
    vector<P> ipt(n);
    rep(i,n){
        scanf("%d%d", &ipt[i].first, &ipt[i].second);
        sum_p += ipt[i].second;
    }
    sort(ipt.begin(), ipt.end(), [](P& a, P& b) -> bool{
        int sum_a = a.first + a.second, sum_b = b.first + b.second;
        return sum_a == sum_b ? ( a.first == b.first ? a.second < b.second : a.first < b.first ) : sum_a < sum_b ;
    });
    for(auto [w, p] : ipt){
        if(sum_left + w + p > sum_p)break;
        sum_left += w + p;
        ans++;
    }
    return ans;
}

int main(){
    scanf("%d", &t);
    while(t--)printf("%d\n", solve());
    return 0;
}