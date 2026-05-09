/*アルゴリズムと工夫点(Swap to Gather/CPU: 10 ms Memory: 6376 KB  Length: 495 B)
最終結果を全部試すことを考えると，「1」の塊の位置を地道に考えることになる．
元々の「1」の位置P1,P2,...,Pkとし，最終結果の位置をQ1,Q2,...,Qk(Q(i+1)-Qi==1)とする．
ここで，
・Pi'=Pi-i,Qi'=Qi-iとすると，Qi'は同一の値になる(ただの平行移動なので，解は変化しない)．
・同じ位置に移動させる場合，「1」をその座標の昇順を考えた時の中央値に集合させるのが適切．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
string s;

int main(){
    int i,j;
    ll ans=0;
    scanf("%d",&n);
    cin>>s;
    vector<int> one;
    rep(i,s.length())if(s[i]=='1')one.push_back(i);
    rep(i,one.size())one[i]-=i;
    j=one[one.size()/2];
    rep(i,one.size())ans+=abs(j-one[i]);
    printf("%lld\n",ans);
    return 0;
}