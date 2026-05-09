/*アルゴリズムと工夫点(Magic For Balls（★3）/CPU: 45 ms Memory: 4032 KB  Length: 1202 B)
xの公約数は素朴な素数判定法を用いた方法で，O(√x)で求めることができる．
それができれば，整数xのボールに対して行う最小の操作回数f(x)とすると，xの約数x'として，f(x)=1+max(f(x'),f(x/x'))となる．
ここで，f(x)の値をメモ化しておくことで，高速に解を求めることができる．
※mapにおいて，keyという「キー」が存在するかはmap.find(key)!=map.end()かで判定できる．
※初見ACできた!
※キーワード:「O(√N)での素因数分解」
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll n;

vector<ll> int2Facs(ll x){
    int i,j;
    vector<ll> tmp;
    for(i=1;(ll)i*i<=x;i++){
        if(x%i==0){
            tmp.push_back(i);
            tmp.push_back(x/i);            
        }
    }
    sort(tmp.begin(),tmp.end());
    tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
    //printf("%lld:",x);rep(i,tmp.size())printf("%lld ",tmp[i]);puts("");
    return tmp;
}

int main(){
    int i,j;
    scanf("%lld",&n);
    map<ll,int> memo;
    const int INF=1000;
    auto res=[&](auto& f,ll x)->int{
        if(memo.find(x)!=memo.end())return memo[x];
        int i,min=INF,tmp;
        vector<ll> facs=int2Facs(x);
        if(facs[1]==x)return memo[x]=0;
        rep(i,facs.size()){
            if(facs[i]==1||facs[i]==x)continue;
            if((tmp=1+max(f(f,facs[i]),f(f,x/facs[i])))<min)
                min=tmp;
        }
        //printf("res(%lld)=%d\n",x,min);
        return memo[x]=min;
    };
    printf("%d\n",res(res,n));
    return 0;
}