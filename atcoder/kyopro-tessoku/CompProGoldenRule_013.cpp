/*アルゴリズムと工夫点(Close Pairs/CPU: 11 ms Memory: 3852 KB  Length: 436 B)
被りなく数え上げるためには，重複する要素を無視した探索範囲で探索し，数え上げる．
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
    ll ans=0,tmp=0;
    scanf("%d%d",&n,&k);
    vector<int> a(n);
    rep(i,n)scanf("%d",&a[i]);
    rep(i,n)ans+=upper_bound(a.begin(),a.end(),a[i]+k)-(a.begin()+i)-1;
    printf("%lld\n",ans);
    return 0;
}