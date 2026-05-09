/*アルゴリズムと工夫点(Factorial and Multiple/CPU: 3 ms Memory: 3940 KB  Length: 1591 B)
素朴な素数判定アルゴリズムでも，素因数分解は可能であり，O(√x)で可能であり，エラトステネスだと時間がかかりすぎる大きな数でも対応可能．
あるNに含まれる素因数xの数cntはルジャンドルの定理でO(logx(N))で数え上げることができ，Nの大きさに対してcntは単調増加するから，二分探索可能．
※初見3完...悔しい
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_P (int)(1e6)
#define MAX_N (long long)(1e18)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<ll,int> p;

ll k;

vector<p> num2PF(ll k){
    int i;
    vector<p> pF;
    ll kk=k;
    p now;
    if(kk%2==0){
        now.first=2;
        now.second=0;
        while(kk%2==0){
            kk/=2;
            now.second++;
        }
        pF.push_back(now);
    }
    for(i=3;(ll)i*i<=k;i+=2){
        if(kk%i==0){
            now.first=i;
            now.second=0;
            while(kk%i==0){
                kk/=i;
                now.second++;
            }
            pF.push_back(now);
        }
    }
    if(kk>1)
        pF.push_back(p(kk,1));
    return pF;
}

ll count(ll p,ll x){
    ll cnt=0,pp=p;
    while(x>=pp){
        cnt+=x/pp;
        pp*=p;
    }
    return cnt;
}

ll search(p x,ll kk){
    ll left=kk+1,right=k+1,mid;
    while(left<right){
        mid=(left+right)/2;
        if(count(x.first,mid)<x.second)
            left=mid+1;
        else
            right=mid;
    }
    return left;
}

int main(){
    int i;
    scanf("%lld",&k);
    vector<p> pF=num2PF(k);
    ll now=1;
    rep(i,pF.size()){
        if(count(pF[pF.size()-1-i].first,now)<pF[pF.size()-1-i].second)
            now=search(pF[pF.size()-1-i],now);
        //printf("p:(%lld,%d),now:%lld\n",pF[pF.size()-1-i].first,pF[pF.size()-1-i].second,now);
    }
    printf("%lld\n",now);
    return 0;
}