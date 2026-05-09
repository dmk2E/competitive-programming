/*アルゴリズムと工夫点(Critical Hit/CPU: 3 ms Memory: 4192 KB  Length: 647 B)
期待値求める問題でも，メモ化再帰等のDPを用いることができることがあり，疑うようにする．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,p;

int power(int x,int a){
    if(a==0)return 1;
    ll res=power(((ll)x*x)%MOD,a/2);
    if(a%2==1)
        res=(res*x)%MOD;
    return res;
}

int main(){
    int i,inv100=power(100,MOD-2);
    ll sum=0;
    scanf("%d%d",&n,&p);
    vector<int> dp(n+1);
    dp[0]=0;dp[1]=1;
    for(i=2;i<=n;i++)
        dp[i]=(1+((((ll)p*inv100)%MOD)*dp[i-2])%MOD+((((100-(ll)p)*inv100)%MOD)*dp[i-1])%MOD)%MOD;
    printf("%d\n",dp[n]);
    return 0;
}