/*アルゴリズムと工夫点(AABCC/CPU: 6 ms Memory: 4988 KB  Length: 1305 B)
N=a*a*b*c*c>a*a*a*a*a=a^5 (∵a<b<c)より、0<a<N^(1/5)となる。aの値を固定すると、N/a^2=b*c*c>b*b*b=b^3 より、0<b<(N/a^2)^(1/3) となる。N=10^12の時、0<a<10^(12/5),0<b<10^(12/3)となるから、12/5+4=32/5<10^7 の計算
量で(a,b)の組を全探索することができる。(a,b)の値の組を固定すれば、cの値は二分探索で求めることができる。a=2,b=3の時、cの値は最大となり、その値はc^2=N/(b*a^2)=10^12/(3*2^2)<10^11より、0<c<10^(11/2)<10^(6)となる。
したがって、0~10^6の間に存在する素数の値をエラトステネスの篩で全列挙しておき、処理を行えばよい。最悪計算量はO(N*log2(log2(N))+10^7*log2(√N))となる。しかし実際は、(a,b,c)は素数の組でないといけないため、計算量はかなり
小さくなる(列挙する素数の数は10^5未満となっている)。
※一発AC嬉しい!
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_PRIME 1000000
using namespace std;

long long n;
vector<int> prime;

void init(){
    int i,j;
    bool isPrime[MAX_PRIME];
    rep(i,MAX_PRIME)
        isPrime[i]=true;
    isPrime[0]=isPrime[1]=false;
    for(i=2;i<MAX_PRIME;i++){
        if(isPrime[i]){
            j=2*i;
            prime.push_back(i);
            while(j<MAX_PRIME){
                isPrime[j]=false;
                j+=i;
            }
        }
    }
}

int main(){
    int a,b,left,right,mid,cnt=0;
    long long temp;
    init();
    scanf("%lld",&n);
    for(a=0;(long long)prime[a]*prime[a]*prime[a]*prime[a]*prime[a]<n;a++){
        for(b=a+1;(long long)prime[a]*prime[a]*prime[b]*prime[b]*prime[b]<n;b++){
            temp=(long long)prime[a]*prime[a]*prime[b];
            left=b+1;right=prime.size();
            while(left<right){
                mid=(left+right)/2;
                if(temp*prime[mid]*prime[mid]<=n)
                    left=mid+1;
                else
                    right=mid;
            }
            //printf("a:%d b:%d c:[%d,%d)\n",prime[a],prime[b],prime[b+1],prime[left]);
            cnt+=left-b-1;
        }
    }
    printf("%d\n",cnt);
    return 0;
}