/*アルゴリズムと工夫点(Most Valuable Parentheses/CPU: 61 ms Memory: 7472 KB  Length: 656 B)
(->+1,)->-1 する状態変数nowを考えると，正しい括弧列となるためには，
・どのタイミングでもnow>=0である必要がある
・最後はnow=0 である必要がある
という条件に言い換えることができる．
-->奇数番目の段階で，必ず1個どこを(とするか決める必要がある
-->奇数番目の段階で，それまでの最大値
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t,n;

ll solve(int n){
    int i,j;
    ll ans=0;
    vector<ll> a(2*n);
    priority_queue<int> PQ;
    rep(i,2*n)scanf("%lld",&a[i]);
    ans+=a[0];
    for(i=1;i<2*n;i++){
        PQ.push(a[i]);
        if(i%2==0){
            ans+=PQ.top();PQ.pop();
        }
    }
    return ans;
}

int main(){
    int i,j;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        printf("%lld\n",solve(n));
    }
    return 0;
}