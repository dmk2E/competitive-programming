/*アルゴリズムと工夫点(Cheese/CPU: 69 ms Memory: 5620 KB  Length: 677 B)
1gずつ使えるから，Aiの値が大きい順に使えるだけ使えばよい．最悪計算量はO(N*low2(N))≒10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> p;

int n,w;

int main(){
    int i,j;
    ll ans=0;
    scanf("%d%d",&n,&w);
    vector<p> ipt(n);
    rep(i,n)
        scanf("%d%d",&ipt[i].first,&ipt[i].second);
    sort(ipt.rbegin(),ipt.rend());
    rep(i,n){
        if(w-ipt[i].second>=0){
            ans+=(ll)ipt[i].first*ipt[i].second;
            w-=ipt[i].second;
        }else{
            ans+=(ll)ipt[i].first*w;
            break;
        }
    }
    printf("%lld\n",ans);
    return 0;
}