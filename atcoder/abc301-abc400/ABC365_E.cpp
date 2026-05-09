/*アルゴリズムと工夫点(Xor Sigma Problem/CPU: 54 ms Memory: 30768 KB  Length: 843 B)
累積和ならぬ累積XORを求めて，利用する．部分XORの値は，S[r+1]xorS[l]で求めることができる．
※ビット毎に考えると分かりやすくなる．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_KETA 32
using namespace std;
typedef long long ll;

int n;
vector<ll> a;
vector<int> sum[MAX_KETA+1];

int main(){
    int i,j,k;
    ll tmp=1,ans=0;
    scanf("%d",&n);
    a=vector<ll>(n);
    rep(i,n)
        scanf("%lld",&a[i]);
    rep(i,MAX_KETA+1){
        sum[i]=vector<int>(n+1);
        sum[i][0]=0;
        //printf("keta:%d\n",i);
        rep(j,n){
            sum[i][j+1]=((a[j]&((ll)1<<i))/((ll)1<<i))^(sum[i][j]);
            //printf("(%lld)^(%d)=%d\n",(a[j]&((ll)1<<i))/((ll)1<<i),sum[i][j],sum[i][j+1]);
        }
    }
    rep(i,MAX_KETA+1){
        k=0;
        rep(j,n+1)if(sum[i][j])k++;
        ans+=(ll)k*(n+1-k)*((ll)1<<i);
    }
    rep(i,n)ans-=a[i];//累積和において，幅1の区間はできないから
    printf("%lld\n",ans);
    return 0;
}