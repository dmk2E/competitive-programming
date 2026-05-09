/*アルゴリズムと工夫点(Happy New Year 2023/CPU:  ms Memory:  KB  Length:  B)
p<=qの時，N=p^(2)*q>=p^3 よって，p<N^(1/3) p>qの時，N=p^(2)*q>q^3 q<N^(1/3) 
従って，それぞれの場合分けで，p,qのどちらかを固定して，条件を満たすか確認すればよい．
ここで，sqrt関数は必ずしも正確とは限らないから，二分探索を用いること．
※初見4完!嬉しい!
*/
#include<iostream>
#include<vector>
#include<cmath>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_PRIME (ll)(3e6)
#define MAX_N (ull)(9e18)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;
ull n;
vector<ll> prime;

void init(){
    ll i,j;
    vector<bool> isPrime(MAX_PRIME,true);
    isPrime[0]=isPrime[1]=false;
    for(i=2;(ull)i*i*i<=MAX_N;i++){
        if(isPrime[i]){
            prime.push_back(i);
            j=2*i;
            while(j<MAX_PRIME){
                isPrime[j]=false;
                j+=i;
            }
        }
    }
}

void ans(ull n){
    int i;
    ull tmp;
    for(i=0;i<prime.size()&&(ull)prime[i]*prime[i]*prime[i]<=n;i++){//p<=qの時
        if(n%((ull)prime[i]*prime[i])==0){
            printf("%lld %llu\n",prime[i],n/((ull)prime[i]*prime[i]));
            return ;
        }
    }
    for(i=0;i<prime.size()&&(ull)prime[i]*prime[i]*prime[i]<=n;i++){//p>qの時
        if(n%prime[i]==0&&n%((ull)prime[i]*prime[i])>0){
            tmp=n/prime[i];
            ull left=2,right=tmp,mid;
            while(left<right){
                mid=(left+right)/2;
                if(mid<(tmp+mid-1)/mid)//オーバーフロー対策
                    left=mid+1;
                else
                    right=mid;            
            }
            printf("%llu %lld\n",left,prime[i]);
            return ;
        }
    }
}

int main(){
    int i;
    init();
    //printf("size:%d\n",(int)prime.size());rep(i,100)printf("%lld\n",prime[i]);
    scanf("%d",&t);
    while(t--){
        scanf("%llu",&n);
        ans(n);
    }
    return 0;
}