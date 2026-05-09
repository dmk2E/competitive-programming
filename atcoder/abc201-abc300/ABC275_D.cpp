/*アルゴリズムと工夫点(Yet Another Recursive Function/CPU: 1 ms Memory: 3992 KB  Length: 438 B)
メモ化再帰で解ける．
*/
#include<iostream>
#include<map>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll n;

int main(){
    int i,j;
    scanf("%lld",&n);
    map<ll,ll> v;
    auto f=[&](auto &ff,ll n)->ll{
        if(n==0)return 1;
        if(v.find(n)!=v.end())return v[n];
        return v[n]=ff(ff,n/2)+ff(ff,n/3);
    };
    printf("%lld\n",f(f,n));
    return 0;
}