/*アルゴリズムと工夫点(Bus Stops/CPU: 1321 ms Memory: 4368 KB  Length: 1061 B)
周期性を利用する．
高橋君の家を出発する時刻と，各バス停間の移動の仕方には周期性が存在する．
従って，前処理で各時刻に対する解を求め，クエリに対しては高速に解を出力すればよい．
最悪計算量は，O(lcm(T[1:N]) * N + Q) < 10^8 となり間に合う．
※ N個の期間Tiの周期が存在する時，全体の周期はlcm(T1, T2, ..., TN) となる
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,x,y,q;

int gcd(int a,int b){
    return b == 0 ? a : gcd(b, a%b);
}

int lcm(int a, int b){
    return a / gcd(a, b) * b;
}

int main(){
    int i,j = 1;
    scanf("%d%d%d",&n,&x,&y);
    vector<int> p(n - 1), t(n - 1);
    rep(i,n - 1){
        scanf("%d%d",&p[i], &t[i]);
        j = lcm(j, p[i]);
    }
    const int MAX_T = j;
    vector<ll> t_to_time(MAX_T);
    auto calcTime = [&](int s) -> ll{
        ll ans = y;
        int i;
        rep(i, n - 1){
            int wait_time = (p[i] - s % p[i]) % p[i];
            ans += wait_time + t[i];
            s = (s + wait_time + t[i]) % MAX_T;
        }
        return ans;
    };
    rep(i,MAX_T)t_to_time[i] = calcTime(i);
    scanf("%d",&q);
    while(q--){
        int s;
        scanf("%d",&s);
        printf("%lld\n",x + s + t_to_time[(s + x) % MAX_T]);
    }
    return 0;
}