/*アルゴリズムと工夫点(Transmission Mission/CPU: 131 ms Memory: 11420 KB  Length: 523 B)
貪欲法で解く．
家の座標は昇順にソートしておく．
この時，家i～家jをカバーするためには，電波強度 (家jの座標)-(家iの座標) の基地局を，2つの家の中点に配置するのが良い．
よって，M=1 の時の最小の電波強度の総和は，Σ(i=1~N-1) X_(i+1)-X_(i) となる．
ここでM=2 の時の解を考えると，任意のi(1<=i<N) について，1つのX_(i+1)-X_(i) を無くしたものとなる．
従ってその差の値を，max(Xi)-min(Xi)の値から降順にM回引けば，問題の解を求めることができる．
最悪計算量は，O(N*log2(N))<10^7 となり高速．
※上手く考察できるかが肝
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    vector<ll> x(n),diff;
    rep(i,n)scanf("%lld",&x[i]);
    sort(x.begin(),x.end());
    rep(i,n-1)diff.push_back(x[i+1]-x[i]);
    sort(diff.begin(),diff.end());
    ll sum=0;
    rep(i,n-m)sum+=diff[i];
    printf("%lld\n",sum);
    return 0;
}