/*アルゴリズムと工夫点(Submask/CPU: 5 ms Memory: 3996 KB  Length: 422 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll n;

int main(){
    int i,j;
    ll sub;
    vector<ll> ans;
    scanf("%lld",&n);
    sub=n;
    do{
        ans.push_back(sub);
        sub=(sub-1)&n;
    }while(sub!=n);
    rep(i,ans.size())printf("%lld\n",ans[ans.size()-1-i]);
    return 0;
}