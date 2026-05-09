/*アルゴリズムと工夫点(Takahashi and Animals/CPU: 35 ms Memory: 9164 KB  Length: 895 B)
条件を満たすような餌の上げ方が存在する時，餌のやり方の順番に関わらず，費用の合計値は変わらない．
よって，先頭の動物から順番に餌をあげていくことを考える．
これは，以下のようなDPで解く．
dp[i][j]:A1~A(i+1)円の餌を買うかどうか決めた時，動物jまで餌をあげた時の費用の最小の合計値
ただし，動物1への餌のあげ方については2通りの場合それぞれについてDPする．
最悪計算量は O(N)<10^6 となり十分高速．
※境界部分で，網羅できていない餌のあげ方が存在してしまうことに気づかず，2WA.....
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    const ll INF=(ll)(1e15);
    vector<int> a(n);
    vector<ll> dp_1(n,INF),dp_n(n-1,INF);
    rep(i,n)scanf("%d",&a[i]);
    dp_1[0]=dp_1[1]=a[0];
    for(i=1;i<n-1;i++){
        dp_1[i+1]=min(dp_1[i+1],dp_1[i]+a[i]);
        if(i+2<n)dp_1[i+2]=min(dp_1[i+2],dp_1[i]+a[i+1]);
    }
    dp_1[n-1]=min(dp_1[n-1],dp_1[n-2]+a[n-1]);
    dp_n[0]=a[n-1];
    rep(i,n-2){
        dp_n[i+1]=min(dp_n[i+1],dp_n[i]+a[i]);
        if(i+2<n-1)dp_n[i+2]=min(dp_n[i+2],dp_n[i]+a[i+1]);
    }
    dp_n[n-2]=min(dp_n[n-2],dp_n[n-3]+a[n-2]);
    //printf("%lld %lld\n",dp_1[n-1],dp_n[n-2]);
    printf("%lld\n",min(dp_1[n-1],dp_n[n-2]));
    return 0;
}