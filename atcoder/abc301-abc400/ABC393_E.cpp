/*アルゴリズムと工夫点(GCD of Subset/CPU: 223 ms Memory: 26484 KB  Length: 703 B)
最大公約数(G,C,D)が，特定の値aとなるかを見定めるのは難しいが，ある値gの倍数であるかの判定は選んだ数全てがgの倍数であるかで判定できる．
そこでまず，c[i]=(配列Aの内，iの倍数である数) を求めておく．
それを元に，各値を含んで選んだ時の解を求めればよい．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_A (int)(1e6)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,k;

int main(){
    int i,j;
    scanf("%d%d",&n,&k);
    vector<int> a(n),c(MAX_A+1,0),a2Cnt(MAX_A+1,0),mx(MAX_A+1,1);
    rep(i,n){
        scanf("%d",&a[i]);
        a2Cnt[a[i]]++;
    }
    for(i=1;i<=MAX_A;i++){
        j=i;
        while(j<=MAX_A){
            c[i]+=a2Cnt[j];
            j+=i;
        }
    }
    for(i=1;i<=MAX_A;i++){
        if(c[i]<k)continue;
        for(j=i;j<=MAX_A;j+=i)mx[j]=i;
    }
    rep(i,n)printf("%d\n",mx[a[i]]);
    return 0;
}