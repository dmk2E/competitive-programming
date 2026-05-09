/*アルゴリズムと工夫点(9 Divisors/CPU: 11 ms Memory: 4600 KB  Length: 1041 B)
約数の個数は，素因数分解して，N=p1^(q1)*p2^(q2)...となる時，(q1+1)*(q2+1)*...となる．これが9となるには，1*9,3*3,9*1 となる必要があるから，(q1,q2)=(0,8),(2,2) しか有り得ない．
よって，p1,p2<=√N としても問題ないため，この範囲で素数を全列挙し，尺取り法でN以下となる(p1,p2)の組を全列挙すればよい．
最悪計算量は，O(√N*log(log(√N)))<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<cmath>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll n;

vector<int> erato(int mx){
    int i,j;
    vector<int> ans;
    vector<bool> isPrime(mx+1,true);
    isPrime[0]=isPrime[1]=false;
    for(i=2;i<=mx;i++){
        if(isPrime[i]){
            j=2*i;
            ans.push_back(i);
            while(j<=mx){
                isPrime[j]=false;
                j+=i;
            }
        }
    }
    return ans;
}

int main(){
    int i,l,r;
    ll ans=0;
    scanf("%lld",&n);
    vector<int> prime=erato((int)sqrt(n)+1);
    i=0;
    while(i<(int)prime.size()&&((ll)prime[i]*prime[i]*prime[i]*prime[i]*prime[i]*prime[i]*prime[i]*prime[i])<=n){
        ans++;
        i++;
    }
    for(l=0,r=(int)prime.size()-1;l<r;l++){
        while(l<r&&!((ll)prime[l]*prime[l]<=n/((ll)prime[r]*prime[r])))
            r--;
        ans+=r-l;
    }
    printf("%lld\n",ans);
    return 0;
}