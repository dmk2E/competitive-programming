/*アルゴリズムと工夫点(Together Square/CPU: 3 ms Memory: 4836 KB  Length: 623 B)
1~Nの整数について，それらが持つ素因数に着目すると，正の整数の組(i,j)が平方数となるためには，平方数でできるだけ割って残った因数が同じであればよい．
よって，各整数について平方数でできるだけ割った数で分類し，数え上げる．
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
    vector<int> num_to_cty(n+1),cnt(n+1,0);
    rep(i,n+1)num_to_cty[i]=i;
    for(i=2;i<=n/i;i++){
        int x=i*i;
        j=x;
        while(j<=n){
            while(num_to_cty[j]%x==0)num_to_cty[j]/=x;
            j+=x;
        }
    }
    rep(i,n)cnt[num_to_cty[i+1]]++;
    ll ans=0;
    rep(i,n+1)ans+=(ll)cnt[i]*cnt[i];
    printf("%lld\n",ans);
    return 0;
}