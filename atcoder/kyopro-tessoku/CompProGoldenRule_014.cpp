/*アルゴリズムと工夫点(Four Boxes/CPU: 67 ms Memory: 7580 KB  Length: 795 B)
A+Bとしてあり得る値を前処理で先に求め，昇順にabで保持．
そうすると，CとDの値を固定した時，ab上で「K-Ci-Di」が存在するか二分探索で求めればよい．
よって最悪計算量はO(N^(2)*log2(N^2))≒10^7 より十分高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,k;

int main(){
    int i,j;
    scanf("%d%d",&n,&k);
    vector<int> ab,a(n),b(n),c(n),d(n);
    rep(i,n)scanf("%d",&a[i]);
    rep(i,n)scanf("%d",&b[i]);
    rep(i,n)scanf("%d",&c[i]);
    rep(i,n)scanf("%d",&d[i]);
    rep(i,n)rep(j,n)ab.push_back(a[i]+b[j]);
    //for(int x: ab)printf("%d ",x);puts("");
    sort(ab.begin(),ab.end());
    rep(i,n)rep(j,n){
        if((*lower_bound(ab.begin(),ab.end(),k-c[i]-d[j]))==k-c[i]-d[j]){
            //printf("%d+c[%d]+d[%d]\n",k-c[i]-d[j],i,j);
            puts("Yes");
            return 0;
        }
    }
    puts("No");
    return 0;
}