/*アルゴリズムと工夫点(Repeated Sequence/CPU: 139 ms Memory: 26000 KB  Length: 670 B)
N個の数列を2回繰り返した数列を元に，累積和+setを用いて解く．
※難しいよ～泣
*/
#include<iostream>
#include<vector>
#include<set>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
ll s;

int main(){
    int i;
    scanf("%d%lld",&n,&s);
    vector<int> a(n);
    vector<ll> sum(2*n+1);
    set<ll> v;
    rep(i,n)scanf("%d",&a[i]);
    sum[0]=0;
    rep(i,2*n)sum[i+1]=sum[i]+a[i%n];
    s%=sum[n];
    if(s==0){
        puts("Yes");
        return 0;
    }
    for(i=2*n;i>=0;i--){
        if(v.find(s+sum[i])!=v.end()){
            puts("Yes");
            return 0;
        }
        v.insert(sum[i]);
    }
    puts("No");
    return 0;
}