/*アルゴリズムと工夫点(Count Arithmetic Subarrays/CPU: 23 ms Memory: 4108 KB  Length: 613 B)
ある(a[l],a[l+1],...,a[r])が等差数列でとなる(l,r)が存在するとき，長さ2以上の等差数列の数は(r-l+1)*(r-l)/2 となる．
よって，長さ2以上の等差数列の数の合計sum(=0で初期化して)とすると，初項a[l]を固定して等差数列でなくなる項a[r+1]を調べ，その部分列から作ることができる長さ2の等差数列の数をsumに加算．
その後，l=rとして，また等差数列でなくなる項を調べて，...というのをl=n-1になるまで繰り返す．
すると，sum+nが解となる．従って，最悪計算量はO(N)<10^6 となり，十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j,l,r;
    ll sum=0;
    scanf("%d",&n);
    vector<int> a(n);
    rep(i,n)
        scanf("%d",&a[i]);
    if(n==1){
        puts("1");
        return 0;
    }
    l=0;r=0;
    while(l<n-1){
        j=a[l+1]-a[l];
        while(r+1<n&&a[r+1]-a[r]==j){
            r++;
            //sum++;
        }
        sum+=((ll)r-l+1)*((ll)r-l)/2;
        l=r;
    }
    printf("%lld\n",sum+n);
    return 0;
}