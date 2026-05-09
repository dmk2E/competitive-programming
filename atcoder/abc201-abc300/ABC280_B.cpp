/*アルゴリズムと工夫点(/CPU:  ms Memory:  KB  Length:  B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i;
    scanf("%d",&n);
    vector<ll> s(n+1,0);
    rep(i,n)
        scanf("%lld",&s[i+1]);
    rep(i,n-1)
        printf("%lld ",s[i+1]-s[i]);
    printf("%lld\n",s[i+1]-s[i]);
    return 0;
}