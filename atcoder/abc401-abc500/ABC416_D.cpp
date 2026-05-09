/*アルゴリズムと工夫点(Match, Mod, Minimize 2/CPU: 101 ms Memory: 5720 KB  Length: 687 B)
貪欲法(+尺取り法)で解く．
求める値は，Σ(Ai+Ai)-C*M (Cは Ai+Bi>=M を満たすiの個数)となり，このCを最大化することを考える．
これは，一方のできるだけ大きい値について，できるだけ小さい値を割り当てる貪欲で良く，尺取り法で実装可能．
最悪計算量は，O(N*log2(N))<10^7 となり高速．
※「X mod M」は，X (X<M) or M-X (X>=M) と同義であり，式の形を変形して考えてみる．
※式変形により，定数が生じれば，解を求めやすくなる．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;

ll solve(){
    int i,j,n,m,cnt=0;
    ll ans=0;
    scanf("%d%d",&n,&m);
    vector<int> a(n),b(n);
    rep(i,n)scanf("%d",&a[i]),ans+=a[i];
    rep(i,n)scanf("%d",&b[i]),ans+=b[i];
    sort(a.rbegin(),a.rend());
    sort(b.begin(),b.end());
    for(i=j=0;i<n;i++){
        while(j<n&&a[i]+b[j]<m)j++;
        cnt+=j<n;
        j++;
    }
    return ans-(ll)cnt*m;
}

int main(){
    scanf("%d",&t);
    while(t--)printf("%lld\n",solve());
    return 0;
}