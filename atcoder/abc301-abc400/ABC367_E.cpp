/*アルゴリズムと工夫点(Permute K times/CPU: 941 ms Memory: 53528 KB  Length: 886 B)
ループに入るのにとても時間がかかるケースも存在するため，シミュレーションは不可．
k回目の操作後のAiはXの値から辿っていくことができる．これに有向グラフを適用すると，「Functional Graph(全ての頂点の出次数が1の有効グラフ)」になる．
この時，ダブリングというテクニックを用いる．これは，iの小さい値から，d[i][v]:頂点vから2^(i)回辿った先の頂点 を順に求める．ここで，d[i+1][v]=d[i][d[i][v]] となる．繰り返し自乗法の1種
ある頂点vからk回辿った先を知りたい場合は，kの2進数表記を参考に，2^(i)の級数で表し，dの値を用いて計算できる．計算量はO(log2(k))
前処理は，頂点数v,辿る最大の値kとして，O(v*log2(k))となる．
最悪計算量はO(N*log2(K))≒10^7 となり，十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_D 60
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
ll k;
vector<int> a,x;

int main(){
    int i,j,ii;
    scanf("%d%lld",&n,&k);
    x=vector<int>(n);
    a=vector<int>(n);
    rep(i,n){
        scanf("%d",&x[i]);
        x[i]--;
    }
    rep(i,n)
        scanf("%d",&a[i]);
    vector<vector<int> > d(MAX_D+1,vector<int>(n));
    vector<int> ans;
    d[0]=x;
    rep(i,MAX_D)rep(j,n)d[i+1][j]=d[i][d[i][j]];
    rep(ii,n-1){
        j=ii;
        rep(i,MAX_D+1){
            if(k&((ll)1<<i)){
                j=d[i][j];
            }
        }
        printf("%d ",a[j]);
    }
    j=ii;
    rep(i,MAX_D+1){
        if(k&((ll)1<<i)){
            j=d[i][j];
        }
    }
    printf("%d\n",a[j]);
    return 0;
}