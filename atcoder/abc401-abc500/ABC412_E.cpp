/*アルゴリズムと工夫点(LCM Sequence/CPU: 715 ms Memory: 123408 KB  Length: 1220 B)
[L+1,R]の間の素数のべき乗の数+1 が解となる．
Ai=([1,i]のLCM) とした時の，Aiの値の変化を観察すると，iが素数のべき乗の所で値が増加していく．
これに気づければ，上記の結論になる．
区間篩というテクニックを用いて，素数のべき乗かの判定を行う．
この時，xが合成数である時，xに対する試し割は，√R以下で良い（素因数分解の要領であるから）．
最悪計算量は，O(√R*log(√R)+√R*log(R))≒10^8 となり間に合う．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_R (int)(1e7)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll l,r;

vector<int> generatePrimeNumbers(int x){
    int i,j;
    vector<int> primes;
    vector<bool> is_prime(x+1,true);
    is_prime[0]=is_prime[1]=false;
    for(i=2;i<=x;i++){
        if(is_prime[i]){
            j=i*2;
            primes.push_back(i);
            while(j<=x){
                is_prime[j]=false;
                j+=i;
            }
        }
    }
    return primes;
}

int main(){
    int i,j;
    vector<int> primes=generatePrimeNumbers(MAX_R);
    scanf("%lld%lld",&l,&r);
    vector<ll> judge(r-l+1);
    rep(i,judge.size())judge[i]=l+i;
    vector<int> cnt(judge.size(),0);
    for(int prime:primes){
        if(r<prime)break;
        i=(prime-l%prime)%prime;
        while(i<judge.size()){
            while(judge[i]%prime==0)judge[i]/=prime;
            cnt[i]++;
            i+=prime;
        }
    }
    j=1;
    rep(i,judge.size()-1){
        if(judge[i+1]!=1)cnt[i+1]++;
        j+=cnt[i+1]==1;
    }
    printf("%d\n",j);
    return 0;
}