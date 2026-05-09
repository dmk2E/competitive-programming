/*アルゴリズムと工夫点(Flush/CPU: 103 ms Memory: 13312 KB  Length: 779 B)
前処理により高速化して解く．
var_to_cnt[b]:同種類のティーをb個選ぶことが可能となる，最小のx
とし，この配列を求める．
これはbの昇順に，フレーバー毎にその個数を表現した棒グラフをイメージしたシミュレーションで求めることができる．
最悪計算量は，O(N*log2(N)+MAX_B+Q)<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_B (int)(1e6)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;//(id,count)

int n,q;

int main(){
    int i,j,min_cnt=0;
    ll cnt=0;
    scanf("%d%d",&n,&q);
    vector<int> a(n);
    const int NIL=-1;
    vector<ll> var_to_cnt(MAX_B+1,NIL);
    rep(i,n)scanf("%d",&a[i]);
    sort(a.begin(),a.end());
    for(j=0,i=1;i<=MAX_B&&j<n;i++){
        var_to_cnt[i]=cnt+1;
        cnt+=n-j;
        min_cnt++;
        while(j<n&&a[j]<=min_cnt)j++;
    }
    while(q--){
        int b;
        scanf("%d",&b);
        printf("%lld\n",var_to_cnt[b]);
    }
    return 0;
}