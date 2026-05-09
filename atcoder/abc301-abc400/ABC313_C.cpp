/*アルゴリズムと工夫点(Approximate Equalization 2/CPU: 34 ms Memory: 4880 KB  Length: 571 B)
ソートを用いて解く．
一意に定まる操作後の分布にするために，必要な操作回数を計算すればよい．
最悪計算量は，O(N*log2(N)) < 10^7 となり高速．
※ 特定の要素を+1, 他の要素を-1 にする-> ある整数から1だけ数を移動させる
※ 何らかの操作を好きな数だけ行う -> 不変量に着目する -> 本問題では，数列の総和が変わらない
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    ll sum_a=0,ans=0;
    scanf("%d",&n);
    vector<int> a(n);
    rep(i,n)scanf("%d",&a[i]),sum_a+=a[i];
    sort(a.begin(),a.end());
    vector<int> b(n,sum_a/n);
    i=sum_a%n;
    j=n-1;
    while(i--){
        b[j]++;
        j--;
    }
    rep(i,n)ans+=max(0,b[i]-a[i]);
    printf("%lld\n",ans);
    return 0;
}