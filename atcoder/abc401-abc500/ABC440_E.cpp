/*アルゴリズムと工夫点(Cookies/CPU: 498 ms Memory: 53512 KB  Length: 1024 B)
優先度付きキューで解く．
最大の美味しさを取るクッキーの選び方から，少しずつ妥協した選び方に遷移するイメージ．
最悪計算量は，O( X * N * log2(N * K) ) < 10 ^ 8 となり，間に合う．
※ ダイクストラ法的な方針
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<set>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<ll, vector<int> > P;

int n, k, x;

int main(){
    int i, j;
    scanf("%d%d%d", &n, &k, &x);
    vector<int> a(n);
    set<vector<int> > v;
    P now(0, n);
    rep(i, n)scanf("%d", &a[i]);
    sort(a.rbegin(), a.rend());
    priority_queue<P> pq;
    now.first = (ll)a[0] * k;
    now.second[0] = k;
    pq.push(now);
    while(x > 0){
        now = pq.top();pq.pop();
        if(v.count(now.second))continue;
        v.insert(now.second);
        printf("%lld\n", now.first);
        x--;
        rep(i, n - 1)if(now.second[i] > 0){
            P nxt = now;
            nxt.first -= a[i];
            nxt.first += a[i + 1];
            nxt.second[i]--;
            nxt.second[i + 1]++;
            pq.push(nxt);
        }
    }
    return 0;
}