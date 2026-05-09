/*アルゴリズムと工夫点(Line Crossing/CPU: 172 ms Memory: 17804 KB  Length: 606 B)
傾きで分類する->上手く情報を正規化できれば良い．
円上の任意の2点(ai,bi)について，(ai+bi)%N で分類することが可能．
よって，傾きごとの集合について，全体の組み合わせの数から引くことを考えればよい．
*/
#include<iostream>
#include<vector>
#include<map>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n,m;

int main(){
    int i,j,k;
    ll ans;
    scanf("%d%d",&n,&m);
    vector<int> a(m),b(m);
    map<int,int> dict;
    ans=((ll)m-1)*m/2;
    rep(i,m){
        scanf("%d%d",&a[i],&b[i]);
        a[i]--;
        b[i]--;
        dict[(a[i]+b[i])%n]++;
    }
    for(auto cnt:dict)ans-=((ll)cnt.second-1)*cnt.second/2;
    printf("%lld\n",ans);
    return 0;
}