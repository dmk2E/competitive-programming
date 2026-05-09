/*アルゴリズムと工夫点(Another Sigma Problem/CPU: 31 ms Memory: 4656 KB  Length: 810 B)
計算途中で扱う数が,10^nの個数であるから,それぞれの個数を保持して置き,計算に用いることで,型のオーバーフローをすることなく,計算することができる.
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 200000
#define MOD 998244353
using namespace std;

int n,a[MAX_N],cntTen[12]={0};
long long ten[12]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000,100000000000};

int count(int x){
    int i;
    rep(i,12){
        if(x<ten[i])
            break;
    }
    return i;
}

int main(){
    int i,j;
    long long ans=0;
    scanf("%d",&n);
    rep(i,n){
        scanf("%d",&a[i]);
        ans=(ans+(long long)a[i]*i)%MOD;
        cntTen[count(a[i])]++;
    }
    rep(i,n-1){
        cntTen[count(a[i])]--;
        rep(j,12){
            ans=(ans+((long long)(((unsigned long long)a[i]*ten[j])%MOD)*cntTen[j])%MOD)%MOD;
        }
    }
    printf("%lld\n",ans);
    return 0;
}